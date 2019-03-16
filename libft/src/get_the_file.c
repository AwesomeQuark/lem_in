/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 09:42:25 by conoel            #+#    #+#             */
/*   Updated: 2019/02/14 05:40:21 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <limits.h>

char	*get_the_file(int fd)
{
	char		*ret;
	char		*tmp;
	char		buffer[BUFF_SIZE + 1];
	size_t		iter_max;

	iter_max = 0;
	ret = NULL;
	ft_bzero(buffer, BUFF_SIZE + 1);
	while (read(fd, buffer, BUFF_SIZE) != 0)
	{
		tmp = ret;
		ret = ft_strjoin(ret, buffer);
		if (tmp != NULL)
			free(tmp);
		if (ft_memchr(buffer, '\0', BUFF_SIZE) != NULL)
			break;
		ft_bzero(buffer, BUFF_SIZE + 1);
		if (iter_max++ > ITER_MAX)
		{
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}