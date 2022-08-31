/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:47:16 by jterrazz          #+#    #+#             */
/*   Updated: 2022/08/31 14:35:58 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"
#include <stdio.h>
#include <unistd.h>

static void test_malloc_null()
{
    void *t = malloc(0);
    if (t)
        printf("malloc(0) should return NULL\n");
    free(t);
}

static void test_malloc_one()
{
    printf("# test_malloc_one\n");
    char *t = (char *)malloc(1);
    if (!t) {
        printf("malloc(1) should return ptr\n");
        return;
    }
    t[0] = 0xFF;
    t[1] = 0xFF;
    t[2] = 0xFF;
    t[3] = 0xFF;
    show_alloc_mem_ex();

    t[0] = 0;
    free(t);
    printf("\n");
}

static void test_malloc_getpagesize()
{
    printf("# test_malloc_getpagesize\n");
    void *t = malloc(getpagesize());
    show_alloc_mem();
    free(t);
    printf("\n");
}

// !!!!!!!!!!!!!!!!
// TODO SHOULD FILL 3 sizes
// CHECK To free all, see if the TINY and SMALL stay
static void test_malloc_limits()
{
    printf("# test_malloc_limits\n");
    void	*t	= malloc(1);
    void	*t0	= malloc(TINY_BLOCK_SIZE);
    void	*t00	= malloc(TINY_BLOCK_SIZE);
    void	*t000	= malloc(TINY_BLOCK_SIZE);
    void	*t1	= malloc(SMALL_BLOCK_SIZE);
    void	*t2	= malloc(SMALL_BLOCK_SIZE + 1);

    // Should print mallocs in all categories (TINY, SMALL, LARGE)
    show_alloc_mem();
    // show_alloc_mem_ex();
    // show_heap_list();
    free(t0);

    t0 = malloc(TINY_BLOCK_SIZE - 32);
    // show_alloc_mem();
    free(t);
    free(t0);
    free(t00);
    free(t000);
    free(t1);
    free(t2);
    printf("\n");
    show_alloc_mem();
    printf("\n");
}

static void test_malloc_free_size()
{
    printf("# test_malloc_free_size\n");
    void *t = malloc(SMALL_BLOCK_SIZE + 1);

    // heap should have 0 free_space
    show_alloc_mem();

    free(t);
    printf("\n");
    show_alloc_mem();
    printf("\n");
}

void run_test_malloc(void)
{
    printf("-- run_test_malloc --\n\n");
    test_malloc_null();
    test_malloc_one();
    test_malloc_getpagesize();
    test_malloc_free_size();
    test_malloc_limits();

    show_alloc_mem_ex();
    printf("\n\n");
    // show_heap_list();
}


    // ft_putstr("data_size: ");
    // ft_itoa_base(block->data_size, 10, 0, FALSE);
    // ft_putstr(" sup to : ");
    // ft_itoa_base(size + 32, 10, 0, FALSE);
    // ft_putstr("\n");
