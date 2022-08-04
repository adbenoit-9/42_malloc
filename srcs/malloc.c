/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/04 18:19:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_state   state = {NULL, NULL};

size_t   get_offset(void)
{
    size_t n = state.free_area - state.heap_begin;
    size_t pagesize = getpagesize();
    if (n % pagesize == 0)
        return (n);
    return ((n / pagesize) * n + pagesize);
} 

void	*malloc(size_t size)
{
    void        *ptr;
    off_t       offset;    

    errno = 0;
    offset = get_offset();
    ptr = mmap(state.free_area, size + 8, PROT_READ | PROT_WRITE, 0, 0, offset);
    if (errno)
        return (NULL);
    if (!state.free_area)
        state.free_area = ptr + size + 8;
    state.free_area += size + 8;
    return (ptr + 8);
}
