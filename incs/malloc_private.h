/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 14:12:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_PRIVATE_H
# define MALLOC_PRIVATE_H

# include "malloc_public.h"
# include "malloc_defs.h"

/*
** Structures
*/

typedef struct s_heap
{
    t_chunk *zones[NZONES];
    t_chunk *bins[NBINS];
}               t_heap;

typedef struct s_mutexes
{
    pthread_mutex_t malloc;
    pthread_mutex_t free;
    pthread_mutex_t realloc;
    pthread_mutex_t print;
}               t_mutexes;

/*
** Global variables
*/

t_heap			g_heap;
t_mutexes       g_mutex = {
    .malloc = PTHREAD_MUTEX_INITIALIZER,
    .realloc = PTHREAD_MUTEX_INITIALIZER,
};

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
t_chunk     *split_chunk(t_chunk *chunk, size_t size);

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
