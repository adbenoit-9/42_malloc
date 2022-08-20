/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs_malloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:34:05 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/20 17:29:55 by adbenoit         ###   ########.fr       */
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

# define MAX_TINY (uint32_t)(getpagesize() / 32)
# define MAX_SMALL (uint32_t)(getpagesize() / 4)

# define ISTINY(size) (size <= MAX_TINY)
# define ISSMALL(size) (size > MAX_TINY && size <= MAX_SMALL)
# define ISLARGE(size) (size > MAX_SMALL)

# define ZONE_SIZE(max) ((max) * 100)
# define ZONE_LIMIT(top, max) ((uint64_t)(top) + (max) * 100 - HEAD_SIZE)
        
#define LITTLE_MALLOC(zone, bin, zone_size) do {\
        if (zone == 0x0) {\
            bin = create_heap(zone_size * 100);\
        }\
		ptr = recycle_chunk(&bin, size);\
		if (zone == 0x0)\
			zone = ptr;\
    } while (0);

/*
** Chunk
*/

/* status */
# define S_TINY 0b1000
# define S_SMALL 0b0100
# define S_LARGE 0b0010
# define S_FREE 0b0001
# define GET_STATUS(n) (n & (S_LARGE | S_SMALL | S_TINY))

/* size */
# define GET_SIZE(n) (n & ~0b1111)
# define HEAD_SIZE 32
# define NEXT_CHUNK(chunk) ((t_chunk *)((void *)(chunk) + ((chunk)->size & ~0b1111)))

typedef struct	s_chunk
{
	size_t			prev_size;		/* Size of previous chunk in memory*/
	size_t			size;			/* Size in bytes, including overhead. */
	struct s_chunk	*previous;		/* pointer to previous chunk in list */
	struct s_chunk	*next;			/* pointer to next chunk in list */
}				t_chunk;

#endif
