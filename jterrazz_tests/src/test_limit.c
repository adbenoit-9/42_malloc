/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_limit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:09:51 by jterrazz          #+#    #+#             */
/*   Updated: 2022/08/31 14:39:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

void run_test_rlimit()
{
    printf("-- run_test_rlimit --\n\n");
    char *t;
    struct rlimit rpl;

    rpl.rlim_cur = TINY_HEAP_ALLOCATION_SIZE;
    rpl.rlim_max = TINY_HEAP_ALLOCATION_SIZE;

    if (setrlimit(RLIMIT_DATA, &rpl) < 0)
        printf("setrlimit did not work\n");

    if (!(t = (char *)malloc(TINY_HEAP_ALLOCATION_SIZE - 1000)))
        printf("malloc() should return ptr\n");
    show_alloc_mem();
    printf("\n");
    free(t);

    if ((t = (char *)malloc(TINY_HEAP_ALLOCATION_SIZE * 10)))
        printf("malloc() should return NULL\n");
    show_alloc_mem();
    free(t);
    printf("\n\n");
}
