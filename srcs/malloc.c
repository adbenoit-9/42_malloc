/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/19 15:13:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	size = (size % 16 == 0 ? size : (size / 16 + 1) * 16) + HEAD_SIZE;
	ptr = NULL;
	pthread_mutex_lock(&g_mutex);
	if (ISTINY(size)) {
		LITTLE_MALLOC(g_tiny_zone, g_tiny_bin, MAX_TINY);
	}
	else if (ISSMALL(size)) {
		LITTLE_MALLOC(g_small_zone, g_small_bin, MAX_SMALL);
	}
	if (!ptr)
		ptr = new_chunk(size, g_large_zone);
	if (ptr && ((t_chunk *)ptr)->size & S_LARGE)
		g_large_zone = ptr;
	pthread_mutex_unlock(&g_mutex);
	if (ptr)
		ptr += HEAD_SIZE;
	return (ptr);
}

void	free(void *ptr)
{
	t_chunk *chunk;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	chunk = (t_chunk *)(ptr - HEAD_SIZE);
	if (chunk->size & S_FREE) {
		write(STDERR_FILENO, "free(): double free detected\n", 30);
		kill(0, SIGABRT);
	}
	if (chunk->size & S_LARGE) {
		chunk = delete_chunk(chunk);
		if (chunk)
			g_large_zone = chunk;
	}
	else if (chunk->size & S_TINY) {
		free_chunk(chunk, g_tiny_bin, ZONE_LIMIT(g_tiny_zone, MAX_TINY));
		merge_free_zone(chunk, &g_tiny_bin, ZONE_LIMIT(g_tiny_zone, MAX_TINY));
	}
	else {
		free_chunk(chunk, g_small_bin, ZONE_LIMIT(g_small_zone, MAX_SMALL));
		merge_free_zone(chunk, &g_small_bin, ZONE_LIMIT(g_small_zone, MAX_SMALL));
	}
	pthread_mutex_unlock(&g_mutex);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_chunk	*chunk;
	t_chunk	*next;

	if (!ptr || size == 0) {
		print_metadata(ptr - HEAD_SIZE);
		free(ptr);
		PRINT("TEST\n");
		return (malloc(size));
	}
	size = (size % 16 == 0 ? size : (size / 16 + 1) * 16) + HEAD_SIZE;
	chunk = ptr - HEAD_SIZE;
	if (GET_SIZE(chunk->size) > size && GET_SIZE(chunk->size) - size > HEAD_SIZE) {
		next = ptr + size;
		next->size = chunk->size - size;
		next->prev_size = size | GET_STATUS(chunk->size);
		chunk->size = size | GET_STATUS(chunk->size);
		free(next + 1);
		return (chunk + 1);
	}
	new_ptr = extend_chunk(chunk, size, chunk->size & S_TINY ? &g_tiny_bin : &g_small_bin,\
			 ZONE_LIMIT(chunk->size & S_TINY ? &g_tiny_zone : &g_small_zone,\
			 	chunk->size & S_TINY ? MAX_TINY : MAX_SMALL));
	if (!new_ptr) {
		new_ptr = malloc(size);
		if (new_ptr) {
			for (size_t i = 0; ((uint8_t *)ptr)[i] && i < size; i++)
				((uint8_t *)new_ptr)[i] = ((uint8_t *)ptr)[i];
		}
		free(ptr);
	}
	else
		new_ptr += HEAD_SIZE;
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	uint64_t	total;
	t_chunk		*top;

	pthread_mutex_lock(&g_mutex);
	total = iter_heap_zone(g_tiny_zone, &print_block, TINY);
	total += iter_heap_zone(g_small_zone, &print_block, SMALL);
	top = g_large_zone;
	while (top && top->next) {
		top = top->next;
	}
	total += iter_heap_zone(top, &print_block, LARGE);
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
