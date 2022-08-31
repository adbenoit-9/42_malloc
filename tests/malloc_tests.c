/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:09 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/31 16:32:10 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include <stdio.h>

void    test_max_malloc_by_zone()
{
    void *ptr;
    
    for (uint16_t i = 0; i < 400; i++) {
        ptr = malloc(3);
    }
    for (uint16_t i = 0; i < 400; i++) {
        ptr = malloc(300);
    }
    show_alloc_mem();
    free(ptr);
}

void    test_n_malloc_by_zone(uint64_t n)
{
    void    *tiny_ptr[n];
    void    *small_ptr[n];
    void    *large_ptr[n];
    
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    for (uint64_t i = 0; i < n; i++) {
        tiny_ptr[i] = malloc(130);
        small_ptr[i] = malloc(3000);
        large_ptr[i] = malloc(50000);
    }
    PRINT("\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    for (uint64_t i = 0; i < n; i++) {
        show_alloc_mem();
        PRINT("---\n");
        free(tiny_ptr[i]);
        free(small_ptr[i]);
        free(large_ptr[i]);
    }
    PRINT("\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
}

void    malloc_tests(void)
{
    PRINT("\n\033[33;1m");
    PRINT("+---------------+\n");
    PRINT("|    malloc     |\n");
    PRINT("+---------------+\n");
    PRINT("\033[0m");
    
    PRINT("\n\033[36;1m# size is equal to 0\033[0m\n");
    void *ptr = malloc(0);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    free(ptr);
    
    PRINT("\n\033[36;1m# simple tests\033[0m\n");
    test_n_malloc_by_zone(5);
    
    PRINT("\n\033[36;1m# use lib functions\033[0m\n");
    char *str = strdup("hello");
    PRINT("\n\033[33mstrdup(\"%s\")\033[0m\n");
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    show_alloc_mem_ex();
    free(str);
    PRINT("\n\033[33mprintf(\"%s %s %f\\n\", \"printf\", \"test\", 2.0)\033[0m\n");
    printf("%s %s %f\n", "printf", "test", 2.0);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    
    // PRINT("\n\033[36;1m# overload zones\033[0m\n");
    // test_max_malloc_by_zone();
    // PRINT("\033[30m");
    // show_alloc_mem();
    // PRINT("\033[0m");
    
}
