/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:03:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 14:07:24 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *create_heap(size_t size)
{
	void    *ptr;

	size = (size % getpagesize() == 0) ? size : \
        (size / getpagesize() + 1) * getpagesize();
    // check limit of mem getrlimit() ?
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE\
		| MAP_ANON, -1, 0);
    if (ptr) {
        ft_bzero(ptr, size);
        ((t_chunk *)ptr)->size = size | S_FREE;
    }
	return (ptr);
}

/* Set a part of a free zone of the heap in use.
    Returns a pointer to the next free zone. */ 
void    *use_free_chunk(t_chunk *free_chunk, size_t size, size_t status)
{
    t_chunk *newptr;
    
    /* delete free chunk */
    if (GET_SIZE(free_chunk->size) < size + HEAD_SIZE) {
        if (free_chunk->previous)
            free_chunk->previous->next = free_chunk->next;
        if (free_chunk->next)
            free_chunk->next->previous = free_chunk->previous;
        newptr = free_chunk->next;
        free_chunk->size = free_chunk->size | status;
        free_chunk->size &= ~S_FREE;
    }
    /* get a part of the free chunk */
    else {
        /* reset the free part */
        newptr = (void *)free_chunk + size;
        newptr->size = GET_SIZE(free_chunk->size) - size;
        newptr->size |= S_FREE;
        newptr->previous = free_chunk->previous;
        newptr->prev_size = size | status;
        newptr->next = free_chunk->next;
        if (newptr->next)
            newptr->next->previous = newptr;
        if (newptr->previous)
            newptr->previous->next = newptr;
        free_chunk->size = size | status;
    }
    /* reset the use part */
    free_chunk->next = 0;
    free_chunk->previous = 0;
    return (newptr);
}

void    *recycle_chunk(t_chunk **bin, size_t size)
{
    uint8_t     zone = ISTINY(size) ? TINY : SMALL;
    t_chunk     *free_chunk, *ptr;

    if ((zone == SMALL && !ISSMALL(size)) || !*bin) {
        return (NULL);
    }
    /* get a free zone to use */
    ptr = *bin;
    while (ptr->next && GET_SIZE(ptr->size) < size) {
        ptr = ptr->next;
    }
    if (!ptr || GET_SIZE(ptr->size) < size) {
        return (NULL);
    }
    free_chunk = use_free_chunk(ptr, size, zone == TINY ? S_TINY : S_SMALL);
    if (!free_chunk || !free_chunk->previous)
        *bin = free_chunk;
    return (ptr);
}

void    *new_chunk(size_t size, t_chunk *next)
{
    t_chunk *chunk;

    chunk = create_heap(size);
    if (!chunk) {
        return (NULL);
    }
    chunk->size &= ~S_FREE;
    chunk->size |= S_LARGE;
    if (next) {
        chunk->next = next;
        chunk->prev_size = next->size;
        next->previous = chunk;
        next->prev_size = chunk->size;
    }
    return (chunk);
}
