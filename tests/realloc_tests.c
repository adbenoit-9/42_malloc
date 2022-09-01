/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 12:06:18 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    realloc_tests(void)
{
    PRINT("\n\033[33;1m");
    PRINT("+---------------+\n");
    PRINT("|    realloc    |\n");
    PRINT("+---------------+\n");
    PRINT("\033[0m");

    void *ptr = realloc(NULL, 40);
    strcpy(ptr, "this is a test of realloc of size 40...");
    PRINT("\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    show_alloc_mem_ex();
    
    PRINT("\n\033[36;1m# new size is larger than the old size\033[0m\n");
    ptr = realloc(ptr, 200);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    
    PRINT("\n\033[36;1m# new size is smaller than the old size\033[0m\n");
    ptr = realloc(ptr, 2);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    show_alloc_mem_ex();
    
    PRINT("\n\033[36;1m# new size is equal to the old size\033[0m\n");
    ptr = realloc(ptr, 2);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    show_alloc_mem_ex();
    
    PRINT("\n\033[36;1m# new size is equal to 0\033[0m\n");
    ptr = realloc(ptr, 0);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    show_alloc_mem_ex();
    
    PRINT("\n\033[36;1m# large new size\033[0m\n");
    ptr = realloc(ptr, 1800000);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    
    free(ptr);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
}
