/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:50:26 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 18:08:54 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	goto_start(size_t *i, char *data, int *line)
{
	long	nb;

	while (data[*i] == '#')
	{
		while (data[*i] != '\n' && data[*i])
			*i += 1;
		*line += 1;
		*i += 1;
	}
	nb = ft_strtoll(&data[(*i)], i, 10);
	if (nb > 2147483647 || nb <= 0)
		return (return_("Error in ants number : Value may be too big or negative"));
	if (data[(*i)++] != '\n')
		return (return_("Error in ants number : wrong format"));
	return (1);
}

static int	error(int line, int type, char c)
{
	if (type == 2)
		ft_printf("Error line %d [char: %c]\n", line, c);
	else
		ft_printf("wrong terminating character line %d\n", line);
	return (0);
}

static int	verify_line(char *data, size_t *i, int line)
{
	while (data[*i] && data[*i] != ' ')
	{
		if (data[*i] == '-')
			return (2);
		*i += 1;
	}
	ft_strtoll(&data[*i], i, 10);
	if (data[(*i)++] != ' ')
		return (error(line, 2, data[(*i) - 1]));
	ft_strtoll(&data[*i], i, 10);
	if (data[*i] != '\n')
		return (error(line, 3, data[*i]));
	return (1);
}

int			verify_data(char *data)
{
	size_t	i;
	int		line;
	int		ret;

	i = 0;
	line = 2;
	if (!(goto_start(&i, data, &line)))
		return (0);
	while (data[i])
	{
		if (data[i] == '#')
			while (data[i] && data[i] != '\n')
				i++;
		else
		{
			ret = verify_line(data, &i, line);
			if (ret == 2)
				return (1);
			if (ret == 0)
				return (0);
		}
		i++;
		line++;
	}
	return (1);
}
