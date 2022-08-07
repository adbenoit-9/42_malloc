/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/07 16:49:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// t_malloc_state   state = {NULL, NULL};

// size_t   get_offset(void)
// {
//     if (!state.free_area || !state.heap_begin)
//         return (0);
//     size_t n = state.free_area - state.heap_begin;
//     size_t pagesize = getpagesize();
//     if (n % pagesize == 0)
//         return (n);
//     return ((n / pagesize) * n + pagesize);
// } 

void	*malloc(size_t size)
{
    void        *ptr;
    // off_t       offset;    

    errno = 0;
    // offset = get_offset();
    (void)size;
    ptr = mmap(NULL, 300, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (errno)
        return (NULL);
    return (ptr + 8);
}
