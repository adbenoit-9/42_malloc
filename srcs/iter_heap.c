/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:41:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 14:01:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs_malloc.h"

static void	print_zone(t_chunk *addr, uint8_t zone)
{
	char		*names[] = {"TINY", "SMALL", "LARGE"};

	PRINT(names[zone]);
	PRINT(" : 0x");
	ft_putnbr_base(ULONG_INT(addr), HEXA);
	PRINT("\n");
}

uint64_t	iter_heap_zone(void *top, void (*funct)(t_chunk *), uint8_t zone)
{
	uint64_t	zones_flag[] = {S_TINY, S_SMALL, S_LARGE};
	uint64_t	total = 0;
	t_chunk		*it = top;

	print_zone(top, zone);
	if (zone == TINY || zone == SMALL) {
		while (it && ULONG_INT(it) < ZONE_LIMIT(top, zone)
				&& it->size & zones_flag[zone]) {
			if (!(it->size & S_FREE)) {
				(*funct)(it);
				total += GET_SIZE(it->size) - HEAD_SIZE;
			}
			it = NEXT_CHUNK(it);
		}
	}
	else {
		while (it) {
			(*funct)(it);
			total += GET_SIZE(it->size) - HEAD_SIZE;
			it = it->next;
		}
	}
	return (total);
}
