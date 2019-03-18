/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:10 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 17:44:12 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

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
	if (!(head = load_structure(raw_data, ant_nb)))
		return (NULL);
	free(raw_data);
	return (head);
}