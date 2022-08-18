/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:00:00 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 16:40:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "libft_malloc.h"
# include "utils.h"
# include <string.h>

void    malloc_tests(void);
void    realloc_tests(void);
void    free_tests(void);
void    *test(size_t n, char *str);

#endif
