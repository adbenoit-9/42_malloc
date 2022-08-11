/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:09 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 19:09:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    tiny_zone(void) {
    char    *ptr;
    
    ptr = malloc(11);
    PRINT("\033[1;33mptr : ");
    ft_putnbr_base(LONG_INT(ptr), HEXA);
    PRINT(" | ");
    strcpy(ptr, "tiny hello");
    PRINT(ptr);
    PRINT("\033[0m\n");
}

void    small_zone(void) {
    char    *ptr;
    
    ptr = malloc(100);
    PRINT("\033[1;33mptr : ");
    ft_putnbr_base(LONG_INT(ptr), HEXA);
    PRINT(" | ");
    strcpy(ptr, "small hello");
    PRINT(ptr);
    PRINT("\033[0m\n");
}

void    large_zone(void) {
    char    *ptr;
    
    ptr = malloc(100000);
    PRINT("\033[1;33mptr : ");
    ft_putnbr_base(LONG_INT(ptr), HEXA);
    PRINT(" | ");
    strcpy(ptr, "large hello");
    PRINT(ptr);
    PRINT("\033[0m\n");
}

void    malloc_tests(void)
{
    show_alloc_mem();
    tiny_zone();
    show_alloc_mem();
    tiny_zone();
    show_alloc_mem();
    small_zone();
    show_alloc_mem();
    // large_zone();
    // show_alloc_mem();
}
