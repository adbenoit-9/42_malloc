/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/11 19:27:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_state   g_state = {
    .zones[TINY] = 0x0,
    .zones[SMALL] = 0x0,
    .zones[LARGE] = 0x0,
    .bins[TINY] = 0x0,
    .bins[SMALL] = 0x0,
    .bins[LARGE] = 0x0,
    };

void    print_chunk(t_chunk *chunk)
{
    PRINT("-- chunk --\nstatus: ");
    if (chunk->size & STATUS_A)
        PRINT("A");
    if (chunk->size & STATUS_M)
        PRINT("M");
    if (chunk->size & STATUS_P)
        PRINT("P");
    PRINT("\nprev_size : ");
    ft_putnbr_base(chunk->prev_size, DEC);
    PRINT(" bytes\nsize : ");
    ft_putnbr_base(GET_SIZE(chunk->size), DEC);
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
    t_chunk *free_ptr = g_state.bins[zone];
    void *ptr;

    if (free_ptr != 0x0) {
        g_state.bins[zone] = free_ptr->next;
        return (free_ptr);
    }
    ptr = g_state.zones[zone];
    while (GET_SIZE(((t_chunk *)ptr)->size) != 0) {
        print_chunk(ptr);
        ptr += (zone == TINY ? MAX_TINY : MAX_SMALL) + HEAD_SIZE;
    }
    return (ptr);
}

void    *alloc(int8_t zone, size_t size, int32_t zone_size)
{
    t_chunk *chunk;

    if (g_state.zones[zone] == 0x0) {
        g_state.zones[zone] = create_heap(zone, zone_size);
        chunk = g_state.zones[zone];
        chunk->size |= STATUS_P;
    }
    else {
        chunk = find_free_space(zone);
    }
    if (chunk == NULL)
        return (NULL);
    chunk->size = size + HEAD_SIZE;
    ((t_chunk *)(chunk + zone_size + HEAD_SIZE))->prev_size = size;
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
