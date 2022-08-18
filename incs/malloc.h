/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 17:41:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft_malloc.h"
# include "defs_malloc.h"

/*
** Global variables
*/

t_chunk	*g_tiny_zone;
t_chunk	*g_small_zone;
t_chunk	*g_large_zone;
t_chunk	*g_tiny_bin;
t_chunk	*g_small_bin;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
** Handle heap functions
*/

void    	*create_heap(size_t size);
void    	*recycle_chunk(t_chunk **bins, size_t size);
void    	*new_chunk(size_t size, t_chunk *next);
void    	set_free_chunk(t_chunk *chunk, size_t size, t_chunk *next, t_chunk *prev);
void        *delete_chunk(t_chunk *chunk);
void        free_chunk(t_chunk *chunk, t_chunk *next);

/*
** Display heap functions
*/

void		print_block(t_chunk *block);
void    	print_chunk(t_chunk *chunk);
void	    hexa_dump(t_chunk *chunk);

/*
** Iter heap functions
*/

uint64_t	iter_heap_zone(void *top, void (*funct)(t_chunk *), uint8_t zone);

#endif
