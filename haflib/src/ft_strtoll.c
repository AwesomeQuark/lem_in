/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:00:20 by conoel            #+#    #+#             */
/*   Updated: 2019/05/22 18:27:03 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_strtoll(char *ptr, size_t *index)
{
	long long	ret;
	int			sign;
	char		maj;
	size_t		i;

	ret = 0;
	maj = 0;
	i = 0;
	while (ft_isspace(ptr[i]))
		i++;
	sign = (ptr[i] == '-') ? -1 : 1;
	ptr[i] == '-' || ptr[i] == '+' ? i++ : 0;
	while (ft_isdigit(ptr[i]))
	{
		ret *= 10;
		ret += ptr[i++] - '0';
	}
	(*index) += i;
	return (ret * sign);
}
