/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:29 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 12:50:29 by adbenoit         ###   ########.fr       */
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
	char	str[20];
	int		j;

	str[0] = ' ';
	str[1] = '|';
	str[18] = '|';
	str[19] = '\n';
	j = 2;
	for (size_t i = 0; i < size; i++, j++) {
		if (i % 16 == 0) {
			PRINT("0x");
			ft_putnbr_base(ULONG_INT(ptr + size), HEXA);
			PRINT(" ");
		}
		if (*(ptr + i) == 0) {
			PRINT("00");
			str[j] = '.';
		}
		else if ((uint8_t)*(ptr + i) < 0x0F) {
			PRINT("0");
		}
		if (*(ptr + i) != 0) {
			ft_putnbr_base((uint8_t)*(ptr + i), HEXA);
			str[j] = ptr[i];
		}
		if ((i + 1) % 16 == 0) {
			j = 1;
			write(STDOUT_FILENO, str, 20);
		}
		else {
			PRINT(".");
		}
	}
}
