/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/19 14:34:33 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    realloc_tests(void)
{
    void *ptr = realloc(NULL, 40);
    strcpy(ptr, "heyyyyyyyyyyyyyyy");
    show_alloc_mem_ex();
    // ptr = realloc(ptr, 200);
    // show_alloc_mem();
    ptr = realloc(ptr, 20);
    show_alloc_mem();
    ptr = strcpy(ptr, "realloc test");
    ptr = realloc(ptr, 1800000);
    show_alloc_mem();
    // free(ptr);
    // show_alloc_mem_ex();
}
