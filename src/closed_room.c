/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:58:02 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 18:35:15 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		compare_weights(t_node **room, int idx)
{
	t_node	*nxt_room;

	nxt_room = (*room)->links[idx];
	if (nxt_room->weight == 0)
		return (1);
	else if (((*room)->weight + 1 < nxt_room->weight)
			&& nxt_room->vzt == VISITED
			&& ft_strcmp((*room)->hist->next->room->name, nxt_room->name))
	{
		remove_path(nxt_room->hist);
		nxt_room->weight = (*room)->weight + 1;
		nxt_room->hist = copy_path((*room)->hist);
		add_path(nxt_room, nxt_room->hist);
		return (1);
	}
	return (0);
}

int		skip_from_close(t_node **room, int idx)
{
	t_node	*check;
	t_path	*tmp;
	int		i;

	i = -1;
	check = NULL;
	tmp = (*room)->hist;
	while (tmp->next)
		tmp = tmp->next;
	check = tmp->prev->room;
	while (ft_strcmp((*room)->links[++i]->name, check->name))
		;
	if (!reverse_flux_case(*room, i) && ((*room)->flux[i] <= 0))
	{
		(*room)->links[idx]->skip = 1;
		return (1);
	}
	return (0);
}

int		check_outwardflux(t_node **room)
{
	int		i;

	i = -1;
	while ((*room)->links[++i])
	{
		if ((*room)->flux[i] == 1)
			return (1);
	}
	return (0);
}

void	reinit_all(t_node *head)
{
	int		i;

	i = -1;
	while (head)
	{
		head->access = OPEN;
		head->vzt = FREE;
		remove_path(head->hist);
		head->weight = 0;
		head->skip = 0;
		head->tag = 0;
		if (head->links)
		{
			while (head->links[++i])
			{
				if (head->flux)
					head->flux[i] = 0;
			}
		}
		i = -1;
		head = head->next;
	}
}

int		check_path_skip(t_node *node, t_path *path, t_path **reinit)
{
	while (path)
	{
		if (!ft_strcmp(node->name, path->room->name))
			return (0);
		path = path->next;
	}
	if (!*reinit)
		*reinit = new_path(node);
	else
		add_path(node, *reinit);
	node->skip = 0;
	return (1);
}
