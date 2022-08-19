/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/19 02:25:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs_malloc.h"

void	print_block(t_chunk *block)
{
	PRINT("0x");
	ft_putnbr_base(ULONG_INT(block + HEAD_SIZE), HEXA);
	PRINT(" - ");
	PRINT("0x");
	ft_putnbr_base(ULONG_INT(block + GET_SIZE(block->size)), HEXA);
	PRINT(" : ");
	ft_putnbr_base(GET_SIZE(block->size) - HEAD_SIZE, DEC);
	PRINT(" bytes\n");
}


void	hexa_dump(t_chunk *chunk)
{
	char	*ptr = (char *)(chunk + 1);
	size_t	size = GET_SIZE(chunk->size) - HEAD_SIZE;

	PRINT("0x");
	ft_putnbr_base(ULONG_INT(ptr), HEXA);
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
