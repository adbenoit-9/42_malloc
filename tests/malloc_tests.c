/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:09 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/07 16:53:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    malloc_tests(void)
{
    char    *ptr;

    ptr = malloc(10);
    // strcpy(ptr, "test 1");
    if (ptr) {
        ft_putnbr_base((int64_t)ptr, "0123456789ABCDEF");
        PRINT("\n");
    }
    else
        PRINT("null\n");
    // show_alloc_mem();
}
