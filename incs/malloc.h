/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/15 15:24:02 by adbenoit         ###   ########.fr       */
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

# define S_TINY 0b1000
# define S_SMALL 0b0100
# define S_LARGE 0b0010
# define S_FREE 0b0001
# define GET_SIZE(n) (n & ~(S_TINY | S_SMALL | S_LARGE | S_FREE))
# define GET_STATUS(n) (n & (S_TINY | S_SMALL | S_LARGE | S_FREE))

# define NBINS 128

/* zones */

# define NZONES 3
# define TINY 0
# define SMALL 1
# define LARGE 2
# define MAX_TINY 21 + HEAD_SIZE
# define MAX_SMALL 65536 + HEAD_SIZE
# define ISTINY(size) (size <= MAX_TINY)
# define ISSMALL(size) (size > MAX_TINY && size <= MAX_SMALL)
# define ISLARGE(size) (size > MAX_SMALL)

# define HEAD_SIZE sizeof(t_chunk)
# define ZONE_SIZE(max) (((HEAD_SIZE + max) * 100 / getsizepage() +\
		(size % getpagesize() == 0)) * getsizepage())

typedef struct	s_chunk
{
	size_t			prev_size;		/* Size of previous chunk in memory*/
	size_t			size;			/* Size in bytes, including overhead. */
	struct s_chunk	*previous;		/* pointer to previous chunk in list */
	struct s_chunk	*next;			/* pointer to next chunk in list */
}				t_chunk;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	ft_putnbr_base(int64_t n, char *base);
void	ft_bzero(void *s, size_t n);
void    *recycle_chunk(t_chunk **bins, size_t size);
void    *new_chunk(t_chunk **zones, size_t size);
void	print_block(t_chunk *block);
void	print_zone(t_chunk *addr, char *name);
void    print_chunk(t_chunk *chunk);
void    *create_heap(size_t size);
void    set_free_chunk(t_chunk *chunk, size_t size, t_chunk *next, t_chunk *prev);

#endif
