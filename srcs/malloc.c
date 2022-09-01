/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 14:12:26 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_private.h"

void	*malloc(size_t size)
{
	void		*ptr;
	uint16_t	zone;

	pthread_mutex_lock(&g_mutex.malloc);
	ptr = NULL;
	if (size) {
		size = ALIGN_BITS(size + HEAD_SIZE);
		if (!ISLARGE(size)) {
			zone = ISTINY(size) ? TINY : SMALL;
			if (g_heap.zones[zone] == 0x0)
				g_heap.bins[zone] = create_heap(MAX_ZONE(zone) * 100);
			ptr = recycle_chunk(&g_heap.bins[zone], size);
			if (g_heap.zones[zone] == 0x0)
				g_heap.zones[zone] = ptr;
		}
		if (!ptr) {
			ptr = new_chunk(size, g_heap.zones[LARGE]);
			if (ptr)
				g_heap.zones[LARGE] = ptr;
		}
		if (ptr)
			ptr += HEAD_SIZE;
	}
	pthread_mutex_unlock(&g_mutex.malloc);
	return (ptr);
}

void	free(void *ptr)
{
	t_chunk		*chunk;
	uint16_t	zone;

	pthread_mutex_lock(&g_mutex.malloc);
	if (ptr)
		chunk = (t_chunk *)(ptr - HEAD_SIZE);
	if (ptr && !STATUS_ERROR(chunk->size) && !(chunk->size & S_FREE)) {
		if (chunk->size & S_LARGE) {
			delete_chunk(chunk, &g_heap.zones[LARGE]);
		}
		else {
			zone = chunk->size & S_TINY ? TINY : SMALL;
			free_chunk(chunk, g_heap.bins[zone], ZONE_LIMIT(g_heap.zones[zone], zone));
			merge_free_zone(chunk, &g_heap.bins[zone], ZONE_LIMIT(g_heap.zones[zone], zone));
			if (GET_SIZE(g_heap.zones[zone]->size) == ZONE_SIZE(zone)) {
				if (munmap(g_heap.zones[zone], GET_SIZE(g_heap.zones[zone]->size)) == 0) {
					g_heap.zones[zone] = 0x0;
					g_heap.bins[zone] = 0x0;
				}
			}
		}
	}
	pthread_mutex_unlock(&g_mutex.malloc);
}

void	*realloc(void *ptr, size_t size)
{
	void		*new_ptr;
	t_chunk		*chunk;
	uint16_t	zone;

	pthread_mutex_lock(&g_mutex.realloc);
	new_ptr = NULL;
	if (ptr) {
		chunk = ptr - HEAD_SIZE;
		if (!STATUS_ERROR(chunk->size) && size) {
			size = ALIGN_BITS(size + HEAD_SIZE);
			if (GET_SIZE(chunk->size) > size &&
					GET_SIZE(chunk->size) - size > HEAD_SIZE) {
				free(split_chunk(chunk, size) + 1);
				new_ptr = ptr;
			}
			else {
				zone = chunk->size & S_TINY ? TINY : SMALL;
				pthread_mutex_lock(&g_mutex.malloc);
				new_ptr = extend_chunk(chunk, size, &g_heap.bins[zone], MAX_ZONE(zone));
				pthread_mutex_unlock(&g_mutex.malloc);
				if (!new_ptr) {
					new_ptr = malloc(size);
					if (new_ptr)
						ft_memcpy(new_ptr, ptr, GET_SIZE(chunk->size) - HEAD_SIZE);
					free(ptr);
				}
				else {
					new_ptr += HEAD_SIZE;
				}
			}
		}
	}
	if (!ptr || size == 0) {
		free(ptr);
		new_ptr = malloc(size);
	}
	pthread_mutex_unlock(&g_mutex.realloc);
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	uint64_t	total;

	pthread_mutex_lock(&g_mutex.malloc);
	total = iter_heap_zone(g_heap.zones[TINY], &print_block, TINY);
	total += iter_heap_zone(g_heap.zones[SMALL], &print_block, SMALL);
	total += iter_heap_zone(g_heap.zones[LARGE], &print_block, LARGE);
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
	pthread_mutex_unlock(&g_mutex.malloc);
}

void	show_alloc_mem_ex()
{
	t_chunk		*top;

	pthread_mutex_lock(&g_mutex.malloc);
	iter_heap_zone(g_heap.zones[TINY], &hexa_dump, TINY);
	iter_heap_zone(g_heap.zones[SMALL], &hexa_dump, SMALL);
	top = g_heap.zones[LARGE];
	while (top && top->next) {
		top = top->next;
	}
	iter_heap_zone(top, &hexa_dump, LARGE);
	pthread_mutex_unlock(&g_mutex.malloc);
}
