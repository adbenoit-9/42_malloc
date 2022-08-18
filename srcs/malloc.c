/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 19:49:19 by adbenoit         ###   ########.fr       */
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
	PRINT("TEST\n");
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
		free_chunk(chunk, g_tiny_bin);
		g_tiny_bin = chunk;
	}
	else {
		free_chunk(chunk, g_small_bin);
		g_small_bin = chunk;
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
	if (size < GET_SIZE(chunk->size)) {
		next = ptr + size;
		next->size = chunk->size - size;
		next->prev_size = size | GET_STATUS(chunk->size);
		chunk->size = size | GET_STATUS(chunk->size);
		PRINT("before free\n");
		show_alloc_mem();
		free(next + 1);
		PRINT("after free\n");
		show_alloc_mem();
		return (chunk + 1);
	}
	new_ptr = extend_chunk(chunk, size, chunk->size & S_TINY ? &g_tiny_bin : &g_small_bin);
	if (!new_ptr) {
		ft_putnbr_base(size, DEC);
		PRINT("\n");
		new_ptr = malloc(size);
		if (new_ptr) {
			for (size_t i = 0; ((uint8_t *)ptr)[i] && i < size; i++)
				((uint8_t *)new_ptr)[i] = ((uint8_t *)ptr)[i];
		}
		free(ptr);
	}
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
