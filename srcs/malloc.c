/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/31 13:13:12 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	size = (size % 16 == 0 ? size : (size / 16 + 1) * 16) + HEAD_SIZE;
	ptr = NULL;
	if (ISTINY(size)) {
		LITTLE_MALLOC(g_tiny_zone, g_tiny_bin, MAX_TINY);
	}
	else if (ISSMALL(size)) {
		LITTLE_MALLOC(g_small_zone, g_small_bin, MAX_SMALL);
	}
	if (!ptr) {
		ptr = new_chunk(size, g_large_zone);
		if (ptr) {
			g_large_zone = ptr;
		}
	}
	if (ptr) {
		ptr += HEAD_SIZE;
	}
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void	free(void *ptr)
{
	t_chunk *chunk;

	pthread_mutex_lock(&g_mutex);
	if (ptr) {
		chunk = (t_chunk *)(ptr - HEAD_SIZE);
		// print_metadata(chunk);
		if (chunk->size & S_FREE) {
			PRINT("---- ");
			ft_putnbr_base(ULONG_INT(ptr), HEXA);
			PRINT("\n");
			// write(STDERR_FILENO, "free(): double free detected\n", 30);
			// kill(0, SIGABRT);
		}
		if (chunk->size & S_LARGE) {
			delete_chunk(chunk, &g_large_zone);
		}
		else if (chunk->size & S_TINY) {
			free_chunk(chunk, g_tiny_bin, ZONE_LIMIT(g_tiny_zone, MAX_TINY));
			// print_metadata(ptr - HEAD_SIZE);
			// g_tiny_bin = chunk;
			merge_free_zone(chunk, &g_tiny_bin, ZONE_LIMIT(g_tiny_zone, MAX_TINY));
		}
		else {
			free_chunk(chunk, g_small_bin, ZONE_LIMIT(g_small_zone, MAX_SMALL));
			// g_small_bin = chunk;
			merge_free_zone(chunk, &g_small_bin, ZONE_LIMIT(g_small_zone, MAX_SMALL));
		}
	}
	pthread_mutex_unlock(&g_mutex);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_chunk	*chunk;
	t_chunk	*next;

	if (!ptr || size == 0) {
		free(ptr);
		return (malloc(size));
	}
	size = (size % 16 == 0 ? size : (size / 16 + 1) * 16) + HEAD_SIZE;
	chunk = ptr - HEAD_SIZE;
	if (GET_SIZE(chunk->size) > size && GET_SIZE(chunk->size) - size > HEAD_SIZE) {
		next = ptr + size - HEAD_SIZE;
		next->size = chunk->size - size;
		next->previous = chunk;
		next->next = chunk->next;
		chunk->next = next;
		next->prev_size = size | GET_STATUS(chunk->size);
		chunk->size = size | GET_STATUS(chunk->size);
		free(next + 1);
		new_ptr = ptr;
	}
	else {
		pthread_mutex_lock(&g_mutex);
		new_ptr = extend_chunk(chunk, size, chunk->size & S_TINY ? &g_tiny_bin : &g_small_bin,\
				ZONE_LIMIT(chunk->size & S_TINY ? &g_tiny_zone : &g_small_zone,\
					chunk->size & S_TINY ? MAX_TINY : MAX_SMALL));
		pthread_mutex_unlock(&g_mutex);
		if (!new_ptr) {
			new_ptr = malloc(size);
			if (new_ptr) {
				ft_memcpy(new_ptr, ptr, GET_SIZE(chunk->size) - HEAD_SIZE);
			}
			free(ptr);
		}
		else {
			new_ptr += HEAD_SIZE;
		}
	}
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	uint64_t	total;

	pthread_mutex_lock(&g_mutex);
	total = iter_heap_zone(g_tiny_zone, &print_block, TINY);
	total += iter_heap_zone(g_small_zone, &print_block, SMALL);
	total += iter_heap_zone(g_large_zone, &print_block, LARGE);
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_mem_ex()
{
	t_chunk		*top;

	pthread_mutex_lock(&g_mutex);
	iter_heap_zone(g_tiny_zone, &hexa_dump, TINY);
	iter_heap_zone(g_small_zone, &hexa_dump, SMALL);
	top = g_large_zone;
	while (top && top->next) {
		top = top->next;
	}
	iter_heap_zone(top, &hexa_dump, LARGE);
	pthread_mutex_unlock(&g_mutex);
}
