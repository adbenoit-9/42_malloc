/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:47:22 by jterrazz          #+#    #+#             */
/*   Updated: 2022/08/31 13:49:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "./test.h"

static void realloc_null_ptr() {
    printf("# realloc_null_ptr\n");
	char *t = realloc(NULL, 5);

	if (!t)
		printf("Realloc(NULL, 5) should return ptr");
	show_alloc_mem();
	free(t);
	printf("\n");
}

static void realloc_0() {
    printf("# realloc_0\n");
	char *t = malloc(4);
	t = realloc(t, 0);

	if (t)
		printf("Realloc(ptr, 0) should return NULL");
	show_alloc_mem();
	free(t);
	printf("\n");
}

static void realloc_1() {
    printf("# realloc_1\n");
	char *t = malloc(1);
	show_alloc_mem();
	printf("\n");
	
	t = realloc(t, 1);
	show_alloc_mem();
	printf("\n");

	t = realloc(t, 10);
	show_alloc_mem();
	printf("\n");
	
	t[0] = 'A';
	t[9] = 'A';
	t = realloc(t, TINY_BLOCK_SIZE);
	show_alloc_mem();
	printf("\n");
	
	t = realloc(t, SMALL_BLOCK_SIZE);
	show_alloc_mem();
	printf("\n");
	
	t = realloc(t, SMALL_BLOCK_SIZE + 2);
	show_alloc_mem();
	printf("\n");
	
	t = realloc(t, 10);
	show_alloc_mem();
	printf("\n");

	if (t[0] != 'A' || t[9] != 'A')
		printf("Realloc should copy data");
	show_alloc_mem_ex();
	free(t);
	printf("\n");
}

static void realloc_large()
{
	char    *addr1;
	char    *addr2;
	char    *addr3;

    printf("# realloc_large\n");
	addr1 = (char *)malloc(1 * M1);
	if (addr1)
		strcpy(addr1, "Bonjours\n");
	addr2 = (char *)malloc(16 * M1);
	addr3 = (char *)realloc(addr1, 128* M1);
	if (addr3)
		addr3[127 * M1] = 42;
	show_alloc_mem();
	free(addr3);
	free(addr2);
	// free(addr1);
	show_alloc_mem();
	printf("\n");
}

void run_test_realloc(void)
{
    printf("-- run_test_realloc --\n\n");
	realloc_null_ptr();
	realloc_0();
	realloc_1();
	realloc_large();
	printf("\n\n");
}
