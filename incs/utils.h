/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:52:33 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/18 15:55:26 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdint.h>
#include <unistd.h>
#include <stddef.h>

# define HEXA "0123456789ABCDEF"
# define DEC "0123456789"
# define PRINT(s) write(STDOUT_FILENO, s, ft_strlen(s))
# define ULONG_INT(ptr) (uint64_t)ptr

void	ft_putnbr_base(int64_t n, char *base);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void    print_metadata(void* ptr);

#endif
