/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:15 by conoel            #+#    #+#             */
/*   Updated: 2019/03/21 14:20:35 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static void		print_path(t_path *path)
{
	while (path)
	{
		ft_printf("%s\n", path->node->name);
		path = path->next;
	}
}

static int		find_path(t_node *node, t_path *path)
{
	t_node	*next;

	if (node->role == 2)
		return (1);
	node->access = 0;
	while ((next = get_next_open_link(node)) != NULL)
	{
		add_path(next, path);
		if (find_path(next, path) == 1)
			return (1);
		remove_path(path);
	}
	return (0);
}

int		solver(t_node *head)
{
	t_node *start;
	t_path *path;

	if (!(start = get_start(head)))
	{
		ft_printf("There is no start :(");
		return(0);
	}
	if (!(path = new_path(start)))
		return (return_(NULL));
	if (!(find_path(start, path)))
	{
		ft_printf("<+> No more path :( <+>\n");
		return(0);
	}
	print_path(path);
	return (1);
}
