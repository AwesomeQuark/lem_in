/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:50:26 by conoel            #+#    #+#             */
/*   Updated: 2019/03/20 13:38:24 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static int	error(int line, int type, char c)
{
	ft_printf("Error line %d [char: %c] [type: %d]\n", line, c, type);
	return (0);
}

int			verify_data(char *data)
{
	size_t	i;
	int		line;

	i = 0;
	line = 2;
	ft_strtoll(&data[i], &i, 10);
	if (data[i++] != '\n')
		return (error(line, 1, data[i]));
	while (data[i])
	{
		if (data[i] == '#')
			while (data[i] != '\n')
				i++;
		else
		{
			while (data[i] != ' ')
			{
				if (data[i] == '-')
					return (1);
				i++;
			}
			ft_strtoll(&data[i], &i, 10);
			if (data[i++] != ' ')
				return (error(line, 2, data[i]));
			ft_strtoll(&data[i], &i, 10);
		}
		if (data[i++] != '\n')
			return (error(line, 3, data[i]));
		line++;
	}
	return (1);
}
