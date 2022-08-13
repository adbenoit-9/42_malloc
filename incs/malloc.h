/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/13 20:54:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h> 
# include <sys/resource.h>

# define PRINT(s) write(STDIN_FILENO, s, strlen(s))
# define NONE 0
# define HEXA "0123456789ABCDEF"
# define DEC "0123456789"
# define LONG_INT(ptr) (int64_t)ptr

# define STATUS_A (size_t)1 << (sizeof(size_t) * 8 - 1)
# define STATUS_M (size_t)1 << (sizeof(size_t) * 8 - 2)
# define STATUS_P (size_t)1 << (sizeof(size_t) * 8 - 3)
# define GET_SIZE(n) (n & ~(STATUS_A | STATUS_M | STATUS_P))
# define GET_STATUS(n) (n & (STATUS_A | STATUS_M | STATUS_P))

# define NBINS (uint8_t)128

/* zones */

# define NZONES (uint8_t)3
# define TINY (uint8_t)0
# define SMALL (uint8_t)1
# define LARGE (uint8_t)2
# define MAX_TINY 21
# define MAX_SMALL 65536
# define ISTINY(size) (size <= MAX_TINY)
# define ISSMALL(size) (size > MAX_TINY && size <= MAX_SMALL)
# define ISLARGE(size) (size > MAX_SMALL)

# define HEAD_SIZE sizeof(t_chunk)
# define ZONE_SIZE(max) (((HEAD_SIZE + max) * 100 / getsizepage() +\
		(size % getpagesize() == 0)) * getsizepage())

typedef struct	s_chunk
{
	size_t			prev_size;		/* Size of previous chunk, if it is free. */
	size_t			size;			/* Size in bytes, including overhead. */
	struct s_chunk	*previous;		/* pointer to previous chunk in list */
	struct s_chunk	*next;			/* pointer to next chunk in list -- used only if this chunk is free.*/
	size_t			unused_space;	/* Size in bytes of the unused space. */
}				t_chunk;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	ft_putnbr_base(int64_t n, char *base);
void	ft_bzero(void *s, size_t n);
void    *get_free_addr(t_chunk **bins, size_t size);
void    set_inuse_chunk(t_chunk *chunk, size_t size, size_t status, t_chunk *next);
void	print_block(t_chunk *block);
void	print_zone(t_chunk *addr, char *name);
void    print_chunk(t_chunk *chunk);
void    *create_heap(size_t size);
void    set_free_chunk(t_chunk *chunk, size_t size, t_chunk *next, t_chunk *prev);

#endif
