/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:09 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/12 10:52:46 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    test(size_t n, char *str) {
    char    *ptr;
    
    ptr = malloc(n);
    PRINT("\033[1;33mptr: ");
    ft_putnbr_base(LONG_INT(ptr), HEXA);
    PRINT(" | ");
    strcpy(ptr, str);
    PRINT(ptr);
    PRINT("\033[0m\n");
}

void    malloc_tests(void)
{
    show_alloc_mem();
    for (uint16_t i = 0; i < 95; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        test(13, "tiny hello");
    }
    for (uint16_t i = 0; i < 60; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        test(100, "small hello");
    }
    show_alloc_mem();
}
