/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:55 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/15 15:56:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void    free_tests(void)
{
    void   *ptr;
    
    ptr = test(13, "tiny hello");
    PRINT("# BEFORE FREE:\n");
    show_alloc_mem();
    free(ptr);
    PRINT("# AFTER FREE:\n");
    show_alloc_mem();
    PRINT("\n");
    
    ptr = test(100, "small hello");
    PRINT("# BEFORE FREE:\n");
    show_alloc_mem();
    free(ptr);
    PRINT("# AFTER FREE:\n");
    show_alloc_mem();
    PRINT("\n");
    
    ptr = test(100, "small hello");
    PRINT("# BEFORE FREE:\n");
    show_alloc_mem();
    free(ptr);
    PRINT("# AFTER FREE:\n");
    show_alloc_mem();
    PRINT("\n");
    
    ptr = test(1000000, "large hello");
    PRINT("# BEFORE FREE:\n");
    show_alloc_mem();
    free(ptr);
    PRINT("# AFTER FREE:\n");
    show_alloc_mem();
    free(NULL);
}
