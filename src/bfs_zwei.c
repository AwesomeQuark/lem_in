/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_zwei.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:06:54 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 15:38:00 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	fill_vzt_path(t_node **room, t_node *nxt_room,
		t_path **vzt_nxt, int i)
{
	if (!*vzt_nxt)
	{
		*vzt_nxt = new_path(nxt_room);
		add_path(nxt_room->links[i], *vzt_nxt);
	}
	else
	{
		if (nxt_room->vzt == FREE && !check_outwardflux(room)
				&& !reverse_flux_case(nxt_room, i))
		{
			add_path(nxt_room, *vzt_nxt);
			nxt_room->vzt = VISITED;
		}
		add_path(nxt_room->links[i], *vzt_nxt);
	}
}

void	closed_access_case2(t_node *nxt_room, t_path **vzt_nxt,
		t_path **reinit, int i)
{
	nxt_room = build_path(nxt_room, i);
	nxt_room->links[i]->vzt = VISITED;
	if (nxt_room->links[i]->access == CLSD)
	{
		nxt_room->links[i]->weight = nxt_room->weight - 1;
		closed_access_case(&nxt_room, vzt_nxt, i, reinit);
	}
}

void	closed_access_case(t_node **room, t_path **vzt_nxt,
		int idx, t_path **reinit)
{
	t_node	*nxt_room;
	int		i;

	i = -1;
	nxt_room = (*room)->links[idx];
	if ((*room)->flux[idx] <= 0)
	{
		if ((*room)->access == OPEN && nxt_room->vzt == FREE)
			nxt_room->skip = 1;
		while (nxt_room->links[++i])
		{
			if ((*room)->access == CLSD && nxt_room->hist)
				compare_weights(&nxt_room, i);
			if (reverse_flux_case(nxt_room, i) && nxt_room->links[i]->vzt == 0)
			{
				fill_vzt_path(room, nxt_room, vzt_nxt, i);
				*room = build_path(*room, idx);
				closed_access_case2(nxt_room, vzt_nxt, reinit, i);
				if ((*room)->access == OPEN)
					nxt_room->weight = (*room)->weight + 1;
				break ;
			}
		}
	}
	check_path_skip(nxt_room, *vzt_nxt, reinit);
}
