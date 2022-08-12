/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/12 16:46:34 by adbenoit         ###   ########.fr       */
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

/* zones */

# define NZONES (int8_t)3
# define TINY (int8_t)0
# define SMALL (int8_t)1
# define LARGE (int8_t)2
# define MAX_TINY 21
# define MAX_SMALL 65536
# define ISTINY(size) (size <= MAX_TINY)
# define ISSMALL(size) (size > MAX_TINY && size <= MAX_SMALL)
# define ISLARGE(size) (size > MAX_SMALL)

# define HEAD_SIZE sizeof(t_chunk)

typedef struct	s_chunk
{
	size_t			prev_size;		/* Size of previous chunk, if it is free. */
	size_t			size;			/* Size in bytes, including overhead. */
	struct s_chunk	*previous;		/* pointer to previous chunk in list */
	struct s_chunk	*next;			/* pointer to next chunk in list -- used only if this chunk is free.*/
	size_t			unused_space;	/* Size in bytes of the unused space. */
}				t_chunk;

typedef struct	s_malloc_state
{
	t_chunk	*zones[NZONES];
	t_chunk	*bins[NZONES];
	
}               t_malloc_state;

extern  t_malloc_state   g_state;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	ft_putnbr_base(int64_t n, char *base);
void	ft_bzero(void *s, size_t n);

#endif
