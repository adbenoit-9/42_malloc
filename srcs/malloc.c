/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:49 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/12 15:34:52 by adbenoit         ###   ########.fr       */
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
	size_t	length;

	if (zone != LARGE) {
		length = (size + HEAD_SIZE) * 100;
	}
	else {
		length = size;
	}
	length = (length / getpagesize() + 1) * getpagesize();
	ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED\
		| MAP_ANON, -1, 0);
	ft_bzero(ptr, length);
	if (errno)
		return (0x0);
	return (ptr);
}

void    *find_free_space(int8_t zone, uint32_t zone_size)
{
	t_chunk	*free_ptr = g_state.bins[zone];
	void	*ptr;
	size_t	max;

	if (free_ptr != 0x0) {
		g_state.bins[zone] = free_ptr->next;
		return (free_ptr);
	}
	ptr = g_state.zones[zone];
	max = (((zone_size + HEAD_SIZE) * 100) / getpagesize() + 1) \
		* getpagesize() / (zone_size + HEAD_SIZE);
	for (size_t i = 0; GET_SIZE(((t_chunk *)ptr)->size) != 0; i++) {
		if (i == max - 1)
			return (0x0);
		ptr += zone_size + HEAD_SIZE;
	}
	return (ptr);
}

void    *large_alloc(size_t size)
{
    t_chunk *chunk;

    chunk = create_heap(LARGE, size);
    if (chunk == 0x0)
        return (0x0);
	if (g_state.zones[LARGE] != 0x0) {
        chunk->next = g_state.zones[LARGE];
        g_state.zones[LARGE]->previous = chunk;
    }
    g_state.zones[LARGE] = chunk;
    chunk->size = size;
    return (chunk);
}

void    *alloc(int8_t zone, size_t size, uint32_t zone_size)
{
	t_chunk *chunk;
	size_t	max;

	if (g_state.zones[zone] == 0x0) {
		g_state.zones[zone] = create_heap(zone, zone_size);
		chunk = g_state.zones[zone];
		chunk->size |= STATUS_P;
	}
	else {
		chunk = find_free_space(zone, zone_size);
	}
	if (chunk == 0x0)
		return (large_alloc(size));
	chunk->size = size;
	max = (((zone_size + HEAD_SIZE) * 100) / getpagesize() + 1) \
		* getpagesize() / (zone_size + HEAD_SIZE);
	if (chunk < g_state.zones[zone] + max - 1)
		(chunk + 1)->prev_size = size;
	return (chunk);
}

void	*malloc(size_t size)
{
	void	*ptr;
	
	errno = 0;
	if (ISTINY(size)) {
		ptr = alloc(TINY, size, MAX_TINY);
	}
	else if (ISSMALL(size)) {
		ptr = alloc(SMALL, size, MAX_SMALL);
	}
	else {
		ptr = large_alloc(size);
	}
	if (ptr)
		ptr += HEAD_SIZE;
	return (ptr);
}
