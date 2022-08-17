/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:09 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/17 17:38:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    *test(size_t n, char *str)
{
    char    *ptr;
    
    ptr = malloc(n);
    if (!ptr) {
        PRINT("\033[1;33mptr: NULL\033[0m\n");
        return (NULL);
    }
    PRINT("\033[1;33mptr: ");
    ft_putnbr_base(LONG_INT(ptr), HEXA);
    PRINT(" | ");
    strcpy(ptr, str);
    PRINT(ptr);
    PRINT("\033[0m\n");
    return (ptr);
}

void    test_max_malloc_by_zone()
{
    show_alloc_mem();
    for (uint16_t i = 0; i < 145; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        test(13, "tiny hello");
    }
    for (uint16_t i = 0; i < 145; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        test(100, "small hello");
    }
    show_alloc_mem();
}

void    test_n_malloc_by_zone(uint64_t n)
{
    void    *ptr;
    show_alloc_mem();
    for (uint64_t i = 0; i < n; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        ptr = test(13, "tiny hello");
        free(ptr);
    }
    for (uint64_t i = 0; i < n; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        ptr = test(100, "small hello");
        free(ptr);
    }
    for (uint64_t i = 0; i < n; i++) {
        ft_putnbr_base(i, DEC);
        PRINT(" - ");
        ptr = test(1000000, "large hello");
        free(ptr);
    }
    show_alloc_mem();
}

void    malloc_tests(void)
{
    // test_max_malloc_by_zone();
    test_n_malloc_by_zone(4);
}
