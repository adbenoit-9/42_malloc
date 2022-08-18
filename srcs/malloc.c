/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 17:09:01 by adbenoit         ###   ########.fr       */
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
	if (pthread_mutex_lock(&g_mutex))
		return (NULL);
	if (ISTINY(size)) {
		LITTLE_MALLOC(g_tiny_zone, g_tiny_bin, MAX_TINY);
	}
	else if (ISSMALL(size)) {
		LITTLE_MALLOC(g_small_zone, g_small_bin, MAX_SMALL);
	}
	if (!ptr) {
		ptr = new_chunk(size, g_large_zone);
	}
	if (ptr && ((t_chunk *)ptr)->size & S_LARGE) {
		g_large_zone = ptr;
	}
	pthread_mutex_unlock(&g_mutex);
	if (ptr) {
		ptr += HEAD_SIZE;
	}
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
		if (chunk->next) {
			chunk->next->previous = chunk->previous;
			chunk->next->prev_size = chunk->prev_size;
		}
		if (chunk->previous)
			chunk->previous->next = chunk->next;
		else
			g_large_zone = chunk->next;
		munmap(chunk, GET_SIZE(chunk->size));
	}
	else {
		size_t  size = GET_SIZE(chunk->size);
		ft_bzero(ptr, size - HEAD_SIZE);
		chunk->size |= S_FREE;
		if (chunk->size & S_TINY) {
			chunk->next = g_tiny_zone;
			g_tiny_zone = chunk;
		}
		else {
			chunk->next = g_small_zone;
			g_small_zone = chunk;
		}
		if (chunk->next)
			chunk->next->previous = chunk;
	}
	pthread_mutex_unlock(&g_mutex);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size)
		new_ptr = malloc(size);
	if (ptr && new_ptr)
		for (size_t i = 0; ((uint8_t *)ptr)[i] && i < size; i++)
			((uint8_t *)new_ptr)[i] = ((uint8_t *)ptr)[i];
	free(ptr);
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
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
