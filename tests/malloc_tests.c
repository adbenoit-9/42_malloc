/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:09 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/13 21:10:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    test(size_t n, char *str) {
    char    *ptr;
    
    ptr = malloc(n);
    if (!ptr) {
        PRINT("\033[1;33mptr: NULL\033[0m\n");
        return ;
    }
    PRINT("\033[1;33mptr: ");
    ft_putnbr_base(LONG_INT(ptr), HEXA);
    PRINT(" | ");
    strcpy(ptr, str);
    PRINT(ptr);
    PRINT("\033[0m\n");
}

void    test_max_malloc_by_zone()
{
    show_alloc_mem();
    for (uint16_t i = 0; i < 10; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        test(13, "tiny hello");
    }
    for (uint16_t i = 0; i < 10; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        test(100, "small hello");
    }
    show_alloc_mem();
}

void    malloc_tests(void)
{
    test_max_malloc_by_zone();
}
