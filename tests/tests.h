/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:00:00 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 19:41:28 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "malloc_public.h"
# include "utils.h"
# include <string.h>
# include <stdio.h>
# include <pthread.h>

void    malloc_tests(void);
void    realloc_tests(void);
void    free_tests(void);
void    thread_tests(void);

#endif
