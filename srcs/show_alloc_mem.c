/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/12 15:46:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_block(t_chunk *block)
{
	PRINT("0x");
	ft_putnbr_base(LONG_INT(block + HEAD_SIZE), HEXA);
	PRINT(" - ");
	PRINT("0x");
	ft_putnbr_base(LONG_INT(block + GET_SIZE(block->size)), HEXA);
	PRINT(" : ");
	ft_putnbr_base(GET_SIZE(block->size) - HEAD_SIZE, DEC);
	PRINT(" bytes\n");
}

void	show_alloc_mem(void)
{
	t_chunk		*it;
	char		*zones[] = {"TINY : ", "SMALL : "};
	int			zone_size[] = {MAX_TINY, MAX_SMALL};
	uint64_t	total = 0;
	size_t		size;

	for (uint8_t i = 0; i < NZONES - 1; i++) {
		it = g_state.zones[i];
		PRINT(zones[i]);
		PRINT("0x");
		ft_putnbr_base(LONG_INT(it), HEXA);
		PRINT("\n");
		size = (zone_size[i] + HEAD_SIZE) * 100;
		size = (size / getpagesize() + 1) * getpagesize();
		size_t j = 0;
		while (j < size && it != 0x0) {
			if (GET_SIZE(it->size) > 0) {
				print_block(it);
				total += GET_SIZE(it->size);
			}
			it = (void *)it + it->size + HEAD_SIZE;
			j += it->size + HEAD_SIZE;
		}
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
}
