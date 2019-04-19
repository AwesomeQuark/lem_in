/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_solver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:15 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 14:35:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		find_path(t_node *node, t_path *path)
{
	t_node	*next;

	if (node->role == 2)
		return (1);
	node->access = 0;
	while ((next = get_next_open_link(node)) != NULL)
		if (find_path(next, path) == 1)
			return (1);
	return (0);
}

int				basic_solver(t_node *head)
{
	t_node *start;
	t_path *path;

	if (!(start = get_start(head)) || start->links == NULL)
		return (return_("There is no start"));
	if (!(path = new_path(start)))
		return (return_(NULL));
	if (!(find_path(start, path)))
		return (0);
	reset_nodes(head);
	return (1);
}
