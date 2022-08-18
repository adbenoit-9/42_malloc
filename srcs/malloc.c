/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 14:35:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk	*g_tiny_zone;
t_chunk	*g_small_zone;
t_chunk	*g_large_zone;
t_chunk	*g_tiny_bin;
t_chunk	*g_small_bin;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void	*ptr;

	size = (size % 16 == 0 ? size : (size / 16 + 1) * 16) + HEAD_SIZE;
	ptr = NULL;
	if (pthread_mutex_lock(&g_mutex))
		return (NULL);
	if (ISTINY(size)) {
		if (g_tiny_zone == 0x0) {
			g_tiny_bin = create_heap(MAX_TINY * 100);
		}
		ptr = recycle_chunk(&g_tiny_bin, size);
		if (g_tiny_zone == 0x0)
			g_tiny_zone = ptr;
	}
	else if (ISSMALL(size)) {
		if (g_small_zone == 0x0) {
			g_small_bin = create_heap(MAX_SMALL * 100);
		}
		ptr = recycle_chunk(&g_small_bin, size);
		if (g_small_zone == 0x0)
			g_small_zone = ptr;
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
	t_chunk		*it;
	t_chunk		*zones[] = {g_tiny_zone, g_small_zone};
	char		*zones_name[] = {"TINY", "SMALL"};
	uint64_t	zones_flag[] = {S_TINY, S_SMALL};
	uint64_t	total = 0;

	for (uint8_t i = 0; i < NZONES - 1; i++) {
		it = zones[i];
		print_zone(zones[i], zones_name[i]);
		while (it != 0x0 && GET_STATUS(it->size) & zones_flag[i]) {
			if (!(GET_STATUS(it->size) & S_FREE)) {
				print_block(it);
				total += GET_SIZE(it->size) - HEAD_SIZE;
			}
			it = (void *)it + GET_SIZE(it->size);
		}
	}
	it = g_large_zone;
	while (it && it->next) {
		it = it->next;
	}
	print_zone(it, "LARGE");
	while (it) {
		print_block(it);
		total += GET_SIZE(it->size);
		it = it->previous;
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_mem_ex()
{
	t_chunk		*it;
	t_chunk		*zones[] = {g_tiny_zone, g_small_zone};
	char		*zones_name[] = {"TINY", "SMALL"};
	uint64_t	zones_flag[] = {S_TINY, S_SMALL};
	uint64_t	total = 0;

	pthread_mutex_lock(&g_mutex);
	for (uint8_t i = 0; i < NZONES - 1; i++) {
		it = zones[i];
		print_zone(zones[i], zones_name[i]);
		while (it != 0x0 && GET_STATUS(it->size) & zones_flag[i]) {
			if (!(GET_STATUS(it->size) & S_FREE)) {
				hexa_dump((char *)(it + 1), GET_SIZE(it->size) - HEAD_SIZE);
				total += GET_SIZE(it->size) - HEAD_SIZE;
			}
			it = (void *)it + GET_SIZE(it->size);
		}
	}
	it = g_large_zone;
	while (it && it->next) {
		it = it->next;
	}
	print_zone(it, "LARGE");
	while (it) {
		hexa_dump((char *)(it + 1), GET_SIZE(it->size) - HEAD_SIZE);
		it = it->previous;
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
	pthread_mutex_unlock(&g_mutex);
	
}
