/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:04:55 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 12:43:04 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

struct s_test {
    char             i;
    char            *str;
    struct s_test   *next;    
};

void    struct_tests(void)
{
    struct s_test *tester;
    struct s_test *it;

    tester = (struct s_test *)malloc(sizeof(struct s_test *));
    if (!tester) {
        PRINT("malloc failed !\n");
        return ;
    }
    tester->str = strdup("list");
    tester->i = '0';
    tester->next = 0;
    it = tester;
    for (int i = 0; i < 300; i++) {
        it->next = (struct s_test *)malloc(sizeof(struct s_test *));
        if (!it->next) {
            PRINT("malloc failed !\n");
            return ;
        }
        it = it->next;
        it->str = strdup("list");
        it->i = '1' + i;
        it->next = 0;
    }
    show_alloc_mem_ex();
    PRINT("\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
    while (tester) {
        free(tester->str);
        it = tester;
        tester = tester->next;
        free(it);
    }
    PRINT("\n\033[30m");
    show_alloc_mem();
    PRINT("\033[0m");
}

void zones_tests(void)
{
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

void    free_tests(void)
{
    PRINT("\n\033[33;1m");
    PRINT("+---------------+\n");
    PRINT("|     free      |\n");
    PRINT("+---------------+\n");
    PRINT("\033[0m");
    
    zones_tests();    

    PRINT("\n\033[36;1m# struct tests\033[0m\n");
    struct_tests();
    PRINT("\033[0m");
}
