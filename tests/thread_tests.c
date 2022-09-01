/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2022/09/01 19:43:55 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

struct s_test {
    char             i;
    char            *str;
    struct s_test   *next;    
};

static void    *big_test()
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
    while (tester) {
        free(tester->str);
        it = tester;
        tester = tester->next;
        free(it);
    }
    show_alloc_mem();
	return (NULL);
}

void    thread_tests(void)
{
    PRINT("\n\033[33;1m");
    PRINT("+---------------+\n");
    PRINT("|    realloc    |\n");
    PRINT("+---------------+\n");
    PRINT("\033[0m\n");
    
	pthread_t *thread = malloc(sizeof(pthread_t) * 100);

	int i = 0;
	while (i < 100) {
		if (pthread_create(thread + i, NULL, big_test, NULL)) {
			printf("Error pthread");
		}
		i++;
	}
	i = 0;
	while (i < 100) {
		if (pthread_join(thread[i], NULL)) {
			printf("error pthread join");
		}
		i++;
	}
}
