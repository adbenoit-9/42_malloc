/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2022/09/01 23:31:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

struct s_test {
    char             i;
    char            *str;
    struct s_test   *next;    
};

static void    *routine()
{
    void *ptr;

    for (int i = 0; i < 10; i++) {
        ptr = malloc(10);
        free(ptr);
        ptr = malloc(3000);
        free(ptr);
        ptr = malloc(30000);
        free(ptr);
    }
    show_alloc_mem();
    PRINT("\n");
	return (NULL);
}

void    thread_tests(void)
{
    PRINT("\n\033[33;1m");
    PRINT("+---------------+\n");
    PRINT("|    thread     |\n");
    PRINT("+---------------+\n");
    PRINT("\033[0m\n");
    
	pthread_t *thread = malloc(sizeof(pthread_t) * 10);

	int i = 0;
	while (i < 10) {
		if (pthread_create(thread + i, NULL, routine, NULL)) {
			printf("Error pthread\n");
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (pthread_join(thread[i], NULL)) {
			printf("error pthread join\n");
		}
		i++;
	}
}
