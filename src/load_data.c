/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:10 by conoel            #+#    #+#             */
/*   Updated: 2019/04/02 17:02:39 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static char		*load_raw_data(char *file_name, int argc)
{
	int		fd;
	char	*raw_data;

	if (argc == 2)
	{
		if ((fd = open(file_name, O_RDONLY)) == -1)
			return ((char *)return_("Failed to open the file"));
	}
	else
		fd = 0;
	if (!(raw_data = get_the_file(fd)))
		return ((char *)return_("Failed to read the file"));
	return (raw_data);
}

t_node			*load_map(int argc, char **argv, long *ant_nb)
{
	char	*raw_data;
	t_node	*head;

	if (!(raw_data = load_raw_data(argv[1], argc)))
		return (NULL);
	if (!(verify_data(raw_data)))
	{
		free(raw_data);
		return (NULL);
	}
	if (!(head = load_structure(raw_data, ant_nb)))
	{
		free(raw_data);
		return (NULL);
	}
	free(raw_data);
	return (head);
}
