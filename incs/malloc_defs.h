/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_defs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:34:05 by adbenoit          #+#    #+#             */
/*   Updated: 2022/09/01 14:11:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_DEFS_H
# define MALLOC_DEFS_H

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
# define NBINS 2

# define TINY 0
# define SMALL 1
# define LARGE 2

# define TINY_ZONE_SIZE (uint64_t)(getpagesize() * 25)
# define SMALL_ZONE_SIZE (uint64_t)(getpagesize() * 400)
# define ZONE_SIZE(z) (z == TINY ? TINY_ZONE_SIZE : SMALL_ZONE_SIZE)

# define MAX_TINY (uint32_t)(TINY_ZONE_SIZE / 100)
# define MAX_SMALL (uint32_t)(SMALL_ZONE_SIZE / 100)
# define MAX_ZONE(z) (z == TINY ? MAX_TINY : MAX_SMALL)

# define ISTINY(size) (size <= MAX_TINY)
# define ISSMALL(size) (size > MAX_TINY && size <= MAX_SMALL)
# define ISLARGE(size) (size > MAX_SMALL)

# define ZONE_LIMIT(top, z) ((uint64_t)(top) + ZONE_SIZE(z) - HEAD_SIZE)
# define PAGE_MULTIPLE(n) (((n) / getpagesize() + ((n) % getpagesize == 0 ? 0 : 1)) / getpagesize())
# define ALIGN_BITS(n) ((n) % 16 == 0 ? (n) : ((n) / 16 + 1) * 16)

/*
** Chunk
*/

/* status */
# define S_TINY 0b1000
# define S_SMALL 0b0100
# define S_LARGE 0b0010
# define S_FREE 0b0001
# define GET_STATUS(n) (n & (S_LARGE | S_SMALL | S_TINY))
# define STATUS_ERROR(n) (GET_STATUS(n) != S_LARGE && GET_STATUS(n) != S_SMALL && GET_STATUS(n) != S_TINY)

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
