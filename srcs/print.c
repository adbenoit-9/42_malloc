/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/17 19:03:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    print_chunk(t_chunk *chunk)
{
	if (!chunk) {
		PRINT("-- null chunk --\n");
		return ;
	}
	PRINT("-- ");
	if (chunk->size & S_TINY)
		PRINT("tiny");
	if (chunk->size & S_SMALL)
		PRINT("small");
	if (chunk->size & S_LARGE)
		PRINT("large");
	if (chunk->size & S_FREE)
		PRINT("free");
	PRINT(" chunk --\n");
	PRINT("prev_size : ");
	ft_putnbr_base(GET_SIZE(chunk->prev_size), DEC);
	PRINT(" bytes\nsize : ");
	ft_putnbr_base(GET_SIZE(chunk->size), DEC);
	PRINT(" bytes\nprevious : 0x");
	ft_putnbr_base(LONG_INT(chunk->previous), HEXA);
	PRINT("\nnext : 0x");
	ft_putnbr_base(LONG_INT(chunk->next), HEXA);
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
	ft_putnbr_base(GET_SIZE(block->size) - HEAD_SIZE, DEC);
	PRINT(" bytes\n");
}

void	hexa_dump(char *ptr, size_t size)
{
	PRINT("0x");
	ft_putnbr_base(LONG_INT(ptr), HEXA);
	PRINT("  ");
	for (size_t i = 0; i < size; i++) {
		if (*(ptr + i) == 0)
			PRINT("00");
		else
			ft_putnbr_base(*(ptr + i), HEXA);
		PRINT(" ");
	}
	PRINT("|");
	for (size_t i = 0; i < size; i++) {
		if (ptr[i])
			write(STDOUT_FILENO, &ptr[i], 1);
		else
			write(STDOUT_FILENO, ".", 1);
	}
	PRINT("|\n");
}
