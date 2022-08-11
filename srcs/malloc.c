/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 17:09:20 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_state   g_state = {
    .zones[0] = NULL,
    .zones[1] = NULL,
    .zones[2] = NULL,
    .top = NULL
    };

void    print_chunk(t_chunk *chunk)
{
    PRINT("-- chunk --\nprev_size : ");
    ft_putnbr_base(chunk->prev_size, DEC);
    PRINT(" bytes\nsize : ");
    ft_putnbr_base(chunk->size, DEC);
    PRINT(" bytes\nprevious : 0x");
    ft_putnbr_base(LONG_INT(chunk->previous), HEXA);
    PRINT("\nnext : 0x");
    ft_putnbr_base(LONG_INT(chunk->next), HEXA);
    PRINT("\nunused_space : ");
    ft_putnbr_base(chunk->unused_space, DEC);
    PRINT(" bytes\n-----------\n");
}

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
    t_chunk *it = g_state.zones[zone];
    
    if (!it || it->size == 0)
        return (it);
    while (it->next && it->size != 0) {
        it = it->next;
    }
    if (!it->next)
        return (it + it->size + it->unused_space + HEAD_SIZE);
    return (it);
}

void    *alloc(int8_t zone, size_t size, int32_t zone_size)
{
    t_chunk *chunk;

    if (g_state.zones[zone] == NULL) {
        g_state.zones[zone] = create_heap(zone, zone_size);
        chunk = g_state.zones[zone];
        print_chunk(chunk);
    }
    else {
        chunk = find_free_space(zone);
    }
    if (chunk == NULL)
        return (NULL);
    chunk->size = size;
    if (zone == LARGE)
        chunk->size |= A;
    chunk->unused_space = zone_size - size;
     /* not first chunk */
    if (g_state.zones[zone] != chunk) {
        chunk->previous = (t_chunk *)(chunk - HEAD_SIZE - chunk->prev_size);
        chunk->previous->next = chunk;
    }
    return (chunk);
}

void	*malloc(size_t size)
{
    void        *ptr;

    errno = 0;
    if (ISTINY(size)) {
        ptr = alloc(TINY, size, MAX_TINY);
    }
    else if (ISSMALL(size)) {
        ptr = alloc(SMALL, size, MAX_SMALL);
    }
    else {
        ptr = alloc(LARGE, size, size);
    }
    return (ptr + HEAD_SIZE);
}
