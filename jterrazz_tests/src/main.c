/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2022/08/31 15:14:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./test.h"

struct s_test {
    char             i;
    char            *str;
    struct s_test   *next;    
};

void    *struct_tests()
{
    struct s_test *tester;
    struct s_test *it;

    tester = (struct s_test *)malloc(sizeof(struct s_test *));
    if (!tester) {
        PRINT("malloc failed !\n");
        return (NULL);
    }
    tester->str = strdup("list");
    tester->i = '0';
    tester->next = 0;
    it = tester;
    for (int i = 0; i < 30; i++) {
        it->next = (struct s_test *)malloc(sizeof(struct s_test *));
        if (!it->next) {
            PRINT("malloc failed !\n");
            return (NULL);
        }
        it = it->next;
        it->str = strdup("list");
        it->i = '1' + i;
        it->next = 0;
    }
    // show_alloc_mem_ex();
    while (tester) {
        free(tester->str);
        it = tester;
        tester = tester->next;
        free(it);
    }
    show_alloc_mem();
	return (NULL);
}

int main(void) {
	pthread_t *thread = malloc(sizeof(pthread_t) * 100);

	run_test_malloc();
	run_test_realloc();
	run_test_mixed();

	int i = 0;
	while (i < 100) {
		if (pthread_create(thread + i, NULL, struct_tests, NULL)) {
			printf("Error pthread");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 100) {
		if (pthread_join(thread[i], NULL)) {
			printf("error pthread join");
			return (1);
		}
		i++;
	}
	run_test_rlimit(); // Always at the end
}
