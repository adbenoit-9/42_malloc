/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/15 15:06:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk	*g_zones[NZONES];
t_chunk	*g_bins[NBINS];

void	*malloc(size_t size)
{
	void	*ptr;
	int		zone;

	size = size % 16 == 0 ? size : (size / 16 + 1) * 16;
	if (ISLARGE(size)) {
		ptr = new_chunk(g_zones, size + HEAD_SIZE);
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
		}
	}
	if (ptr) {
		ptr += HEAD_SIZE;
	}
	return (ptr);
}

void	free(void *ptr)
{
    t_chunk *chunk = (t_chunk *)(ptr - HEAD_SIZE);

    if (chunk->size & S_LARGE) {
        munmap(ptr, GET_SIZE(chunk->size));
    }
    else {
        size_t  size = GET_SIZE(chunk->size);
        ft_bzero(chunk + HEAD_SIZE, size);
        chunk->size = size;
        // add_to_bin(chunk);
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
				total += GET_SIZE(it->size);
			}
			it = (void *)it + GET_SIZE(it->size);
		}
	}
	it = g_zones[LARGE];
	while (it && it->next) {
		it = it->next;
	}
	print_zone(it, "LARGE");
	while (it && it->previous) {
		print_block(it);
		total += GET_SIZE(it->size);
		it = it->previous;
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
}
