/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:15:40 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 19:41:50 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int main(int ac, char **av)
{
    int test_on[4] = {1, 1, 1, 1};

    if (ac != 1) {
        ft_bzero(test_on, 4 * sizeof(int));
        for (int i = 0; av[i]; i++) {
            if (strcmp(av[i], "malloc") == 0)
                test_on[0] = 1;
            else if (strcmp(av[i], "free") == 0)
                test_on[1] = 1;
            else if (strcmp(av[i], "realloc") == 0)
                test_on[2] = 1;
            else if (strcmp(av[i], "thread") == 0)
                test_on[3] = 1;
        }
    }
    if (test_on[0])
        malloc_tests();
    if (test_on[1])
        free_tests();
    if (test_on[2])
        realloc_tests();
    if (test_on[3])
        thread_tests();
    return (0);
}
