/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:35:36 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/07 16:53:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_putnbr_base(int64_t n, char *base)
{
	if (n == 0)
		write(STDIN_FILENO, "0", 1);
	else
	{
		if (n < 0)
		{
			write(STDIN_FILENO, "-", 1);
			n *= -1;
		}
		if (n > 0)
		{
			if (n / strlen(base) != 0)
				ft_putnbr_base(n / strlen(base), base);
			write(STDIN_FILENO, &base[n % strlen(base)], 1);
		}
	}
}
