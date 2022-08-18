/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs_malloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:34:05 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 16:03:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_MALLOC_H
# define DEFS_MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h> 
# include <sys/resource.h>
# include <pthread.h>
# include <signal.h>
# include "utils.h"

/*
** Zones
*/

# define NZONES 3

# define TINY 0
# define SMALL 1
# define LARGE 2

# define MAX_TINY 128
# define MAX_SMALL 1024

# define ISTINY(size) (size <= MAX_TINY)
# define ISSMALL(size) (size > MAX_TINY && size <= MAX_SMALL)
# define ISLARGE(size) (size > MAX_SMALL)

# define ZONE_SIZE(max) (((HEAD_SIZE + max) * 100 / getsizepage() +\
		(size % getpagesize() == 0)) * getsizepage())

/*
** Chunk
*/

/* status */
# define S_TINY 0b1000
# define S_SMALL 0b0100
# define S_LARGE 0b0010
# define S_FREE 0b0001

/* size */
# define GET_SIZE(n) (n & ~(S_TINY | S_SMALL | S_LARGE | S_FREE))
# define HEAD_SIZE sizeof(t_chunk)

typedef struct	s_chunk
{
	size_t			prev_size;		/* Size of previous chunk in memory*/
	size_t			size;			/* Size in bytes, including overhead. */
	struct s_chunk	*previous;		/* pointer to previous chunk in list */
	struct s_chunk	*next;			/* pointer to next chunk in list */
}				t_chunk;

#endif
