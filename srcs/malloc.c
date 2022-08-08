/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/08 19:59:37 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_state   state = {
    .bins[0] = NULL,
    .bins[1] = NULL,
    .bins[2] = NULL,
    .top = NULL};

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

    errno = 0;
    // if (ISTINY(size)) {
    //     tiny_malloc(size);
    // }
    // if (ISMALL(size)) {
    //     small_malloc(size);
    // }
    // else {
    //     large_malloc(size);
    // }
    ptr = mmap(NULL, 300, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (errno)
        return (NULL);
    return (ptr + 8);
}
