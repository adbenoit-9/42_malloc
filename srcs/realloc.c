/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:12:45 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/04 11:24:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size) {
		new_ptr = malloc(size);
		if (!new_ptr)
			return (NULL);
	}
	for (size_t i = 0; ((unsigned char *)ptr)[i] && i < size; i++)
		((unsigned char *)new_ptr)[i] = ((unsigned char *)ptr)[i];
	free(ptr);
	return (new_ptr);
}
