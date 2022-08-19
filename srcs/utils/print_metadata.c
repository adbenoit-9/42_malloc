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

void    print_metadata(void* ptr)
{
	if (!ptr) {
		PRINT("-- null pointer --\n");
		return ;
	}
	PRINT("-- ");
	if (*(size_t *)(ptr + 8) & 0b1000)
		PRINT("tiny");
	if (*(size_t *)(ptr + 8) & 0b0100)
		PRINT("small");
	if (*(size_t *)(ptr + 8) & 0b0010)
		PRINT("large");
	if (*(size_t *)(ptr + 8) & 0b0001)
		PRINT("_free");
	PRINT(" chunk 0x");
	ft_putnbr_base(ULONG_INT(ptr), HEXA);
	PRINT("--\nprev_size : ");
	if (*(size_t *)ptr == 0)
		PRINT("0");
	else
		ft_putnbr_base((*(size_t *)ptr & ~0b1111) - 32, DEC);
	PRINT(" bytes | status : ");
	ft_putnbr_base(*(size_t *)ptr & 0b1111, DEC);
	PRINT("\nsize : ");
	ft_putnbr_base((*(size_t *)(ptr + 8) & ~0b1111) - 32, DEC);
	PRINT(" bytes\nprevious : 0x");
	ft_putnbr_base(*(long int *)(ptr + 16), HEXA);
	PRINT("\nnext : 0x");
	ft_putnbr_base(*(long int *)(ptr + 24), HEXA);
	PRINT("\n-----------\n");
}
