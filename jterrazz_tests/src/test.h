/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:17:19 by jterrazz          #+#    #+#             */
/*   Updated: 2022/08/31 12:52:12 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_TEST
# define MALLOC_TEST

# include "libft_malloc.h"
# include <pthread.h>
# include "utils.h"
# include <string.h>

# define TINY_BLOCK_SIZE (uint32_t)(getpagesize() / 32) - 32
# define SMALL_BLOCK_SIZE (uint32_t)(getpagesize() / 4) - 32
# define TINY_HEAP_ALLOCATION_SIZE (uint32_t)(getpagesize() / 32) * 100
# define M1 (1024 * 1024)

void run_test_malloc(void);
void run_test_realloc(void);
void run_test_mixed(void);
void show_heap_list();
void run_test_rlimit();

#endif
