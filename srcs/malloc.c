/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/17 15:54:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk	*g_zones[NZONES];
t_chunk	*g_bins[NBINS];

void	*malloc(size_t size)
{
	void	*ptr;
	int		zone;

	PRINT("in malloc\n");
	size = size % 16 == 0 ? size : (size / 16 + 1) * 16;
	if (ISLARGE(size)) {
		ptr = new_chunk(g_zones, size + HEAD_SIZE);
		PRINT("failed1\n");
	}
	else {
		zone = ISTINY(size) ? TINY : SMALL;
		if (g_zones[zone] == 0x0) {
			g_bins[zone] = create_heap((zone == TINY ? MAX_TINY : MAX_SMALL) * 100);
		}
		ptr = recycle_chunk(g_bins, size + HEAD_SIZE);
		if (g_zones[zone] == 0x0)
			g_zones[zone] = ptr;
		if (!ptr) {
			ptr = new_chunk(g_zones, size + HEAD_SIZE);
			PRINT("failed2\n");
		}
	}
	print_chunk(ptr);
	if (ptr) {
		ptr += HEAD_SIZE;
	}
	PRINT("chunk create\n");
	return (ptr);
}

void	free(void *ptr)
{
	t_chunk *chunk;
	uint8_t zone;

	PRINT("in free\n");
	ft_putnbr_base(LONG_INT(ptr), HEXA);
	PRINT("\n");
	if (!ptr)
		return ;
	chunk = (t_chunk *)(ptr - HEAD_SIZE);
	print_chunk(chunk);
	if (chunk->size & S_LARGE) {
		if (chunk->next) {
			chunk->next->previous = chunk->previous;
			chunk->next->prev_size = chunk->prev_size;
		}
		else
		if (chunk->previous)
			chunk->previous->next = chunk->next;
		else
			g_zones[LARGE] = chunk->next;
		munmap(chunk, GET_SIZE(chunk->size));
	}
	else {
		PRINT("not in large zone\n");
		size_t  size = GET_SIZE(chunk->size);
		print_chunk(chunk);
		ft_bzero(chunk + HEAD_SIZE, size - HEAD_SIZE);
		chunk->size |= S_FREE;
		zone = chunk->size & S_TINY ? TINY : SMALL;
		chunk->next = g_bins[zone];
		g_bins[zone] = chunk;
		if (chunk->next)
			chunk->next->previous = chunk;
		PRINT("freed\n");
	}
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
	t_chunk		*it;
	char		*zones_name[] = {"TINY", "SMALL"};
	uint64_t	zones_flag[] = {S_TINY, S_SMALL};
	uint64_t	total = 0;

	for (uint8_t i = 0; i < NZONES - 1; i++) {
		it = g_zones[i];
		print_zone(g_zones[i], zones_name[i]);
		while (it != 0x0 && GET_STATUS(it->size) & zones_flag[i]) {
			if (!(GET_STATUS(it->size) & S_FREE)) {
				print_block(it);
				total += GET_SIZE(it->size) - HEAD_SIZE;
			}
			it = (void *)it + GET_SIZE(it->size);
		}
	}
	it = g_zones[LARGE];
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
}
