/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 19:40:26 by adbenoit         ###   ########.fr       */
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
	uint32_t	zones_size[] = {MAX_TINY + HEAD_SIZE, MAX_SMALL + HEAD_SIZE};
	uint64_t	total = 0;

	for (uint8_t i = 0; i < NZONES - 1; i++) {
		it = g_state.zones[i];
		PRINT(zones[i]);
		PRINT("0x");
		ft_putnbr_base(LONG_INT(it), HEXA);
		PRINT("\n");
		for (uint32_t j = 0; j < 100 && it != 0x0; j++) {
			if (GET_SIZE(it->size) > HEAD_SIZE) {
				print_block(it);
				total += GET_SIZE(it->size) - HEAD_SIZE;
			}
			it = (void *)it + zones_size[i];
		}
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
}
