/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:03:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 17:37:47 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs_malloc.h"

void    *create_heap(size_t size)
{
	void    *ptr;

	size = (size % getpagesize() == 0) ? size : \
        (size / getpagesize() + 1) * getpagesize();
    // check limit of mem getrlimit() ?
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
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
    free_chunk->next = 0;
    free_chunk->previous = 0;
    return (newptr);
}

/* Get a free zone pre-allocate on the heap */
void    *recycle_chunk(t_chunk **bin, size_t size)
{
    uint8_t     zone = ISTINY(size) ? TINY : SMALL;
    t_chunk     *free_chunk, *ptr;

    if (!bin || !*bin)
        return (NULL);
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

/* Allocates a new chunk on the heap.
Return a pointer to the begin of the chunk.*/
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

void    free_chunk(t_chunk *chunk, t_chunk *next)
{
    size_t  size = GET_SIZE(chunk->size);
    ft_bzero(chunk + 1, size - HEAD_SIZE);
    chunk->size |= S_FREE;
    chunk->next = next;
    if (chunk->next)
        chunk->next->previous = chunk;   
}

void    *delete_chunk(t_chunk *chunk)
{
    void    *ptr = NULL;

    if (chunk->next) {
        chunk->next->previous = chunk->previous;
        chunk->next->prev_size = chunk->prev_size;
    }
    if (chunk->previous)
        chunk->previous->next = chunk->next;
    else
        ptr = chunk->next;
    munmap(chunk, GET_SIZE(chunk->size));
    return (ptr);
}
