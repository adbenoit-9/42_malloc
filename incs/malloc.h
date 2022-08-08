/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:10:52 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/08 19:58:53 by adbenoit         ###   ########.fr       */
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

# define NBINS 3
// # define NLARGE 128 * 1024
# define PRINT(s) write(STDIN_FILENO, s, strlen(s))

typedef enum	e_bin_type
{
	TINY,
	SMALL,
	LARGE
}				bin_type;

# define ISTINY(size) size < 350 ? true : false
# define ISSMALL(size) size >= 350 && size < 4000 ? true : false
# define ISLARGE(size) size >= 4000 ? true : false

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
	t_chunk	*bins[NBINS];
	void	*top;
	
}               t_malloc_state;

extern  t_malloc_state   state;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	ft_putnbr_base(int64_t n, char *base);

#endif
