/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:03:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/13 21:09:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *create_heap(size_t size)
{
	void    *ptr;

	size = (size % getpagesize() == 0) ? size : \
        (size / getpagesize() + 1) * getpagesize();
    // check limit of mem getrlimit() ?
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED\
		| MAP_ANON, -1, 0);
	if (errno)
		return (0x0);
	ft_bzero(ptr, size);
    ((t_chunk *)ptr)->size = size | STATUS_P;
	return (ptr);
}

void    *get_free_addr(t_chunk **bins, size_t size)
{
    uint8_t     zone = ISTINY(size) ? TINY : SMALL;
    uint32_t    max_sizes[] = {MAX_TINY, MAX_SMALL};
    t_chunk     *ptr, *prev;

    if (zone == SMALL && !ISSMALL(size)) {
        return (NULL);
    }
    else if (bins[zone] == 0x0) {
        ptr = create_heap((max_sizes[zone] + HEAD_SIZE) * 100);
        bins[zone] = ptr;
    }
    ptr = bins[zone];
    prev = bins[zone];
    while (ptr->next && GET_SIZE(ptr->size) < size) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr)
        return (NULL);
    if (ptr->size == size)
        prev->next = ptr->next;
    else {
        if (prev->next)
            prev->next->prev_size = size;
        set_free_chunk((void *)(ptr + 1) + size, GET_SIZE(ptr->size) - size,
            ptr->next, prev);
    }
    if (prev == bins[zone])
        bins[zone] = (void *)(ptr + 1) + size;
    return (ptr);
}

void    set_free_chunk(t_chunk *chunk, size_t size, t_chunk *next, t_chunk *prev)
{
    // ft_bzero(chunk, size);
    if (chunk) {
        chunk->size = size | STATUS_P;
        chunk->next = next;
        if (next)
            next->previous = chunk;
        if (prev) {
            prev->next = chunk;
            chunk->previous = prev;
        }
    }
}

void    set_inuse_chunk(t_chunk *chunk, size_t size, size_t status, t_chunk *next)
{
    if (chunk) {
        chunk->size = size | status;
        if (status & STATUS_M) {
            if (next) {
                chunk->next = next;
                next->previous = chunk;
                next->prev_size = chunk->size;
            }
        }
        else {
            if (next) {
                (chunk + 1)->prev_size = chunk->size;
            }
        }
    }
}
