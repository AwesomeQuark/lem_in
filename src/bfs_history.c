/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:51:55 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/05 23:49:01 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*visit_paths(t_node **room, t_path **vzt_nxt, t_path *reinit)
{
	if (!*vzt_nxt)
		return (reinit);
	else
		*room = (*vzt_nxt)->room;
	reinit = deprecate_first(vzt_nxt, reinit);
	return (reinit);
}

int		flux_to_end(t_node **room, t_path **vzt_nxt, int i, t_node *head)
{
	t_path	*tmp;

	if (((*room)->links[i])->role == END && (*room)->flux[i] == 0)
	{
		(*room)->flux[i] = 1;
		shortest_path(room, head);
		while (*vzt_nxt && (*vzt_nxt)->room->role != END)
		{
			(*vzt_nxt)->room->vzt = FREE;
			tmp = *vzt_nxt;
			if ((*vzt_nxt)->room->hist)
			{
				remove_path((*vzt_nxt)->room->hist);
				(*vzt_nxt)->room->hist = NULL;
			}
			*vzt_nxt = (*vzt_nxt)->next;
			free(tmp);
		}
		return (1);
	}
	return (0);
}

t_node	*build_path(t_node *room, int i)
{
	if (room->hist == NULL)
	{
		if (room->links[i]->vzt == FREE)
		{
			room->links[i]->weight++;
			(room->links[i])->hist = new_path(room->links[i]);
		}
	}
	else
	{
		if ((room->links[i])->role == 0 && (room->links[i])->vzt == FREE)
		{
			if (reverse_flux_case(room, i))
				room->links[i]->weight = room->weight - 1;
			else
				room->links[i]->weight = room->weight + 1;
			if (room->links[i]->hist)
				remove_path(room->links[i]->hist);
			(room->links[i])->hist = copy_path(room->hist);
			add_path(room->links[i], (room->links[i])->hist);
		}
	}
	return (room);
}
