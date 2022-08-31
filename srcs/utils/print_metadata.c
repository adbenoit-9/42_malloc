/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_metadata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:52:34 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 22:21:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void 	print_status(size_t status)
{
	if (status & 0b1000)
		PRINT("tiny");
	else if (status & 0b0100)
		PRINT("small");
	else if (status & 0b0010)
		PRINT("large");
	else
		PRINT("none");
	if (status & 0b0001)
		PRINT("_free");
}

void 	print_color(size_t status)
{
	if (status & 0b1000)
		PRINT("\033[36m");
	if (status & 0b0100)
		PRINT("\033[34m");
	if (status & 0b0010)
		PRINT("\033[32m");
}

void    print_metadata(void* ptr)
{
	if (!ptr) {
		PRINT("\033[31m-- null pointer --\033[0m\n");
		return ;
	}
	print_color(*(size_t *)(ptr + 8));
	PRINT("-- ");
	print_status(*(size_t *)(ptr + 8));
	PRINT(" chunk 0x");
	ft_putnbr_base(ULONG_INT(ptr), HEXA);
	PRINT("--\nprev_size : ");
	if (*(size_t *)ptr == 0)
		PRINT("0");
	else
		ft_putnbr_base((*(size_t *)ptr & ~0b1111), DEC);
	PRINT(" bytes | status : ");
	print_status(*(size_t *)(ptr));
	PRINT("\nsize : ");
	ft_putnbr_base((*(size_t *)(ptr + 8) & ~0b1111), DEC);
	PRINT(" bytes\nprevious : 0x");
	ft_putnbr_base(*(long int *)(ptr + 16), HEXA);
	PRINT("\nnext : 0x");
	ft_putnbr_base(*(long int *)(ptr + 24), HEXA);
	PRINT("\n-----------\033[0m\n");
}
