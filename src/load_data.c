/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:10 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 17:10:22 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static t_node	*load_nodes(char *data, int *ant_nb)
{
	size_t	i;
	size_t	j;
	t_node	*head;
	int		pos;

	i = 0;
	head = NULL;
	*ant_nb = ft_strtoll(data, &i, 10);
	i++;
	while (data[i])
	{
		j = 0;
		while (data[i + j] != '\n' && data[i + j])
			j++;
		if (ft_memchr(&data[i], ' ', j) == NULL && data[i] != '#')
			break;
		(ft_memcmp(&data[i], "##start\n", 8) == 0) ? pos = 1 : 0;
		(ft_memcmp(&data[i], "##end\n", 6) == 0) ? pos = 2 : 0;
		if (data[i] != '#')
		{
			if (!(head = add_node(head, &data[i], pos)))
				return (NULL);
			pos = 0;
		}
		i = i + j + 1;
	}
	return (head);
}

static char		*load_raw_data(char *file_name, int argc)
{
	int		fd;
	char	*raw_data;

	if (argc != 2)
		return((char *)return_("Usage : ./lem_in file_name"));
	if (!(fd = open(file_name, O_RDONLY)))
		return((char *)return_("Failed to open the file"));
	if (!(raw_data = get_the_file(fd)))
		return ((char *)return_("Failed to read the file"));
	return (raw_data);
}

t_node			*load_map(int argc, char **argv, int *ant_nb)
{
	char	*raw_data;
	t_node	*head;

	if (!(raw_data = load_raw_data(argv[1], argc)))
		return (NULL);
	if (!(head = load_nodes(raw_data, ant_nb)))
		return (NULL);
	free(raw_data);
	return (head);
}