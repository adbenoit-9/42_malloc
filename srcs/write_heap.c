/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:03:43 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/31 16:44:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs_malloc.h"

void    *create_heap(size_t size)
{
	void            *ptr;
	struct rlimit   rlim;
    int             ret;

    // size = size % getpagesize() ? (size / getpagesize() + 1) * getpagesize() : size;
    ret = getrlimit(RLIMIT_DATA, &rlim);
	if (ret == 0 && rlim.rlim_max > size) {
        ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (ptr != MAP_FAILED) {
            ((t_chunk *)ptr)->size = size | S_FREE;
        }
        else {
            ptr = NULL;
        }
    }
    else {
        ptr = NULL;
    }
	return (ptr);
}

/* Set a part of a free zone of the heap in use.
    Returns a pointer to the next free zone. */ 
void    *use_free_chunk(t_chunk *free_chunk, size_t size, size_t status)
{
    t_chunk *newptr;
    
    /* delete free chunk */
    if (GET_SIZE(free_chunk->size) == size
            || GET_SIZE(free_chunk->size) - size < HEAD_SIZE) {
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
        newptr->size = (free_chunk->size - size) | status;
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

/* Extends the chunk size if there is enough free space */ 
void    *extend_chunk(t_chunk *chunk, size_t size, t_chunk **bin, uint64_t limit)
{
    t_chunk *free_part;
    t_chunk tmp;
    int64_t  add_size;
    
    add_size = size - GET_SIZE(chunk->size);
    if (add_size <= 0)
        return (chunk);
    if (GET_STATUS(chunk->size) & S_LARGE
            || (GET_STATUS(chunk->size) & S_SMALL && !ISSMALL(size))
            || (GET_STATUS(chunk->size) & S_TINY && !ISTINY(size)))
        return (NULL);
    free_part = NEXT_CHUNK(chunk);
    if (ULONG_INT(free_part) > limit || !(free_part->size & S_FREE)
            || free_part->size < (uint64_t)add_size)
        return (NULL);
    tmp = *free_part;
    tmp.size -= add_size;
    tmp.prev_size = size | GET_STATUS(chunk->size);
    ft_memcpy((void *)chunk + size, &tmp, sizeof(tmp));
    if (tmp.previous)
        tmp.previous->next = (void *)chunk + size;
    else
        *bin = (void *)chunk + size;
    chunk->size = size | GET_STATUS(chunk->size);
    return (chunk);
}

/* Get a free zone pre-allocate on the heap */
void    *recycle_chunk(t_chunk **bin, size_t size)
{
    uint8_t     zone = ISTINY(size) ? TINY : SMALL;
    t_chunk     *free_chunk, *ptr;

    if (!bin || !*bin)
        return (NULL);
    ptr = *bin;
    while (ptr->next && GET_SIZE(ptr->size) < size
            && GET_SIZE(ptr->size) - size <= HEAD_SIZE) {
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
    if (chunk) {
        chunk->size &= ~S_FREE;
        chunk->size |= S_LARGE;
        chunk->next = next;
        if (next) {
            next->previous = chunk;
            // next->prev_size = chunk->size;
        }
    }
    return (chunk);
}

void    free_chunk(t_chunk *chunk, t_chunk *next, uint64_t limit)
{
    chunk->size |= S_FREE;
    chunk->next = next;
    chunk->previous = 0x0;
    if (ULONG_INT(NEXT_CHUNK(chunk)) < limit)
        NEXT_CHUNK(chunk)->prev_size = chunk->size;
    if (chunk->next) {
        chunk->next->previous = chunk;
    }
}

void    delete_chunk(t_chunk *chunk, t_chunk **bin)
{
    if (chunk->next) {
        chunk->next->previous = chunk->previous;
        chunk->next->prev_size = chunk->prev_size;
    }
    if (chunk->previous)
        chunk->previous->next = chunk->next;
    else
        *bin = chunk->next;
    munmap(chunk, GET_SIZE(chunk->size));
}

void    merge_free_zone(t_chunk *chunk, t_chunk **bin, uint64_t limit)
{
    t_chunk *prev, *next, *front_merge;
    
    if (!chunk || !(chunk->size & S_FREE))
        return ;
    next = NEXT_CHUNK(chunk);
    front_merge = NULL;
    if (ULONG_INT(next) < limit && next->size & S_FREE) {
        chunk->size += GET_SIZE(next->size);
        if (next->next)
            next->next->previous = next->previous;
        if (next->previous)
            next->previous->next = next->next;
        if (ULONG_INT(NEXT_CHUNK(chunk)) < limit)
            NEXT_CHUNK(chunk)->prev_size = chunk->size;
        // ft_bzero(next, HEAD_SIZE);
    }
    if (chunk->prev_size & S_FREE) {
        prev = (void *)chunk - GET_SIZE(chunk->prev_size);
        front_merge = prev;
        front_merge->size += GET_SIZE(chunk->size);
        if (chunk->next)
            chunk->next->previous = chunk->previous;
        if (chunk->previous)
            chunk->previous->next = chunk->next;
        if (ULONG_INT(NEXT_CHUNK(front_merge)) < limit)
            NEXT_CHUNK(front_merge)->prev_size = front_merge->size;
        // ft_bzero(chunk, HEAD_SIZE);
            
    }
    if (!front_merge) {
        *bin = chunk;
    }
}
