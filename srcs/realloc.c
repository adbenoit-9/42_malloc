/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:45 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/04 14:19:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size)
		new_ptr = malloc(size);
	if (ptr && new_ptr)
		for (size_t i = 0; ((u_int8_t *)ptr)[i] && i < size; i++)
			((u_int8_t *)new_ptr)[i] = ((u_int8_t *)ptr)[i];
	free(ptr);
	return (new_ptr);
}
