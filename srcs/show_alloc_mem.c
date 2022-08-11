/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 17:04:20 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	t_chunk		*it;
	char		*zones[] = {"TINY : ", "SMALL : ", "LARGE : "};
	uint64_t	total = 0;

	for (uint8_t i = 0; i < NZONES; i++) {
		it = g_state.zones[i];
		PRINT(zones[i]);
		PRINT("0x");
		ft_putnbr_base(LONG_INT(it), HEXA);
		PRINT("\n");
		while (it) {
			PRINT("0x");
			ft_putnbr_base(LONG_INT(it + HEAD_SIZE), HEXA);
			PRINT(" - ");
			PRINT("0x");
			ft_putnbr_base(LONG_INT(it + HEAD_SIZE + it->size), HEXA);
			PRINT(" : ");
			ft_putnbr_base(it->size, DEC);
			PRINT(" bytes\n");
			total += it->size;
			it = it->next;
		}
	}
	PRINT("Total : ");
	ft_putnbr_base(total, DEC);
	PRINT("\n");
}
