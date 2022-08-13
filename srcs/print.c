/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/13 20:23:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    print_chunk(t_chunk *chunk)
{
	PRINT("-- chunk --\nstatus: ");
	if (chunk->size & STATUS_A)
		PRINT("A");
	if (chunk->size & STATUS_M)
		PRINT("M");
	if (chunk->size & STATUS_P)
		PRINT("P");
	PRINT("\nprev_size : ");
	ft_putnbr_base(chunk->prev_size, DEC);
	PRINT(" bytes\nsize : ");
	ft_putnbr_base(GET_SIZE(chunk->size), DEC);
	PRINT(" bytes\nprevious : 0x");
	ft_putnbr_base(LONG_INT(chunk->previous), HEXA);
	PRINT("\nnext : 0x");
	ft_putnbr_base(LONG_INT(chunk->next), HEXA);
	PRINT("\nunused_space : ");
	ft_putnbr_base(chunk->unused_space, DEC);
	PRINT(" bytes\n-----------\n");
}

void	print_zone(t_chunk *addr, char *name)
{

	PRINT(name);
	PRINT(" : 0x");
	ft_putnbr_base(LONG_INT(addr), HEXA);
	PRINT("\n");
}

void	print_block(t_chunk *block)
{
	PRINT("0x");
	ft_putnbr_base(LONG_INT(block + HEAD_SIZE), HEXA);
	PRINT(" - ");
	PRINT("0x");
	ft_putnbr_base(LONG_INT(block + GET_SIZE(block->size)), HEXA);
	PRINT(" : ");
	ft_putnbr_base(GET_SIZE(block->size), DEC);
	PRINT(" bytes\n");
}
