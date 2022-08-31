/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/31 16:42:42 by adbenoit         ###   ########.fr       */
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
// pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
** Handle heap functions
*/

void    	*create_heap(size_t size);
void    	*recycle_chunk(t_chunk **bins, size_t size);
void    	*new_chunk(size_t size, t_chunk *next);
void    	set_free_chunk(t_chunk *chunk, size_t size, t_chunk *next, t_chunk *prev);
void        delete_chunk(t_chunk *chunk, t_chunk **bin);
void        free_chunk(t_chunk *chunk, t_chunk *next, uint64_t limit);
void        *extend_chunk(t_chunk *chunk, size_t size, t_chunk **bin, uint64_t limit);
void    	merge_free_zone(t_chunk *chunk, t_chunk **bin, uint64_t limit);

/*
** Display heap functions
*/

void		print_block(t_chunk *block);
void	    hexa_dump(t_chunk *chunk);

/*
** Iter heap functions
*/

uint64_t	iter_heap_zone(void *top, void (*funct)(t_chunk *), uint8_t zone);

#endif
