/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/13 21:09:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk	*g_zones[NZONES];
t_chunk	*g_bins[NBINS];

void	*malloc(size_t size)
{
	void	*ptr;
	size_t	status;
	uint8_t	zone;

	status = NONE;
	size = size % 16 == 0 ? size : (size / 16 + 1) * 16;
	if (ISLARGE(size)) {
		ptr = create_heap(size);
		status = STATUS_M;
		g_zones[LARGE] = ptr;
	}
	else {
		ptr = get_free_addr(g_bins, size);
		if (g_zones[ISTINY(size) ? TINY : SMALL] == 0x0)
			g_zones[ISTINY(size) ? TINY : SMALL] = ptr;
		if (!ptr) {
			ptr = create_heap(size);
			status = STATUS_M;
		}
	}
	if (ptr) {
		if (status & STATUS_M)
			zone = LARGE;
		else if (ISTINY(size))
			zone = TINY;
		else
			zone = SMALL;
		set_inuse_chunk(ptr, size, status, g_zones[zone]);
		ptr += HEAD_SIZE;
	}
	return (ptr);
}

void	free(void *ptr)
{
    t_chunk *chunk = (t_chunk *)(ptr - HEAD_SIZE);

    if (chunk->size & STATUS_M) {
        munmap(ptr, GET_SIZE(chunk->size));
    }
    else if (chunk->size & STATUS_A) {
        return ;
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
	int			zone_size[] = {MAX_TINY, MAX_SMALL};
	char		*zones_name[] = {"TINY", "SMALL"};
	uint64_t	total = 0;
	size_t		size;

	for (uint8_t i = 0; i < NZONES - 1; i++) {
		it = g_zones[i];
		size = (zone_size[i] + HEAD_SIZE) * 100;
		size = (size / getpagesize() + 1) * getpagesize();
		print_zone(g_zones[i], zones_name[i]);
		while (it != 0x0 && it->size != 0) {
			if (GET_SIZE(it->size) > 0) {
				print_block(it);
				total += GET_SIZE(it->size);
			}
			it = (void *)(it + 1) + GET_SIZE(it->size);
		}
	}
	print_zone(g_zones[LARGE], "LARGE");
	it = g_zones[LARGE];
	while (it && it->next)
		it = it->next;
	while (it && it->previous) {
		print_block(it);
		total += GET_SIZE(it->size);
		it = it->previous;
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
}
