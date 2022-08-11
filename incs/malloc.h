/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 17:04:37 by adbenoit         ###   ########.fr       */
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

# define PRINT(s) write(STDIN_FILENO, s, strlen(s))
# define NONE 0
# define HEXA "0123456789ABCDEF"
# define DEC "0123456789"
# define LONG_INT(ptr) (int64_t)ptr

# define A (size_t)1 << (sizeof(size_t) - 1)
# define M (size_t)1 << (sizeof(size_t) - 2)
# define P (size_t)1 << (sizeof(size_t) - 3)

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
	void	*top;
	
}               t_malloc_state;

extern  t_malloc_state   g_state;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	ft_putnbr_base(int64_t n, char *base);
void	ft_bzero(void *s, size_t n);

#endif
