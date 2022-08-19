/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:55 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/19 16:15:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    free_tests(void)
{
    PRINT("\n\033[33;1m");
    PRINT("+---------------+\n");
    PRINT("|     free      |\n");
    PRINT("+---------------+\n");
    PRINT("\033[0m");
    
    void *ptr0 = malloc(40);
    void *ptr1 = malloc(4);
    void *ptr2 = malloc(400);
    void *ptr3 = malloc(700);
    void *ptr4 = malloc(40000);
    void *ptr5 = malloc(45000);
    
    PRINT("\n\033[36;1m# null pointer\033[0m\n");
    free(NULL);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    
    PRINT("\n\033[36;1m# tiny zone\033[0m\n");
    free(ptr0);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    free(ptr1);
    PRINT("-\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    
    PRINT("\n\033[36;1m# small zone\033[0m\n");
    free(ptr2);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    free(ptr3);
    PRINT("-\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    
    PRINT("\n\033[36;1m# large zone\033[0m\n");
    free(ptr4);
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    free(ptr5);
    PRINT("\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
}
