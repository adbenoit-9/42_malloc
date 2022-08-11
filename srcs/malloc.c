/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 13:04:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_state   g_state = {
    .bins[0] = NULL,
    .bins[1] = NULL,
    .bins[2] = NULL,
    .top = NULL};

void    *create_heap(int8_t zone, size_t size)
{
    void    *ptr;

    if (zone != LARGE) {
        ptr = mmap(NULL, (size + HEAD_SIZE) * 100,
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
        ft_bzero(ptr, (size + HEAD_SIZE) * 100);
    }
    else {
        ptr = mmap(NULL, size + HEAD_SIZE,
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
        ft_bzero(ptr, size + HEAD_SIZE);
    }
    if (errno)
        return (NULL);
    return (ptr);
}

void    *find_free_space(int8_t zone)
{
    t_chunk *it = g_state.bins[zone];
    
    return (it);
}

void    *alloc(int8_t zone, size_t size, int16_t zone_size)
{
    t_chunk *chunk;

    if (g_state.bins[zone] == NULL) {
        g_state.bins[zone] = create_heap(zone, size);
        if (!g_state.bins[zone])
            return (NULL);
    }
    chunk = find_free_space(zone);
    if (chunk == NULL)
        return (NULL);
    chunk->size = size;
    chunk->unused_space = zone_size - size;
    if (chunk + zone_size - g_state.bins[zone] > 0) {
        ((t_chunk *)(chunk + zone_size))->prev_size = size;
        ((t_chunk *)(chunk + zone_size))->previous = chunk;
    }
    return (NULL);
}

void	*malloc(size_t size)
{
    void        *ptr;

    errno = 0;
    if (ISTINY(size)) {
        ptr = alloc(TINY, size, MAX_TINY);
    }
    if (ISSMALL(size)) {
        ptr = alloc(SMALL, size, MAX_SMALL);
    }
    else {
        ptr = alloc(LARGE, size, size);
    }
    return (ptr + 8);
}
