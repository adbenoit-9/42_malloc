/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 19:37:50 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    realloc_tests(void)
{
    void *ptr = realloc(NULL, 40);
    strcpy(ptr, "heyyyyyyyyyyyyyyy");
    show_alloc_mem();
    ptr = realloc(ptr, 2);
    show_alloc_mem();
    ptr = realloc(ptr, 18);
    show_alloc_mem();
    // ptr = strcpy(ptr, "realloc test");
    // show_alloc_mem_ex();
    // free(ptr);
    // show_alloc_mem_ex();
}
