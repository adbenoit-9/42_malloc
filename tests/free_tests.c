/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:55 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 23:49:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    free_tests(void)
{
    void    *ptr1;
    void    *ptr2;
    void    *ptr3;

    show_alloc_mem();
    ptr1 = malloc(50);
    ptr2 = malloc(50);
    ptr3 = malloc(50);
    show_alloc_mem();
    free(ptr1);
    show_alloc_mem();
    // print_metadata(ptr1 - 32);
    free(ptr2);
    show_alloc_mem();
    // print_metadata(ptr1 - 32);
    free(ptr3);
    show_alloc_mem();
    // print_metadata(ptr1 - 32);
}
