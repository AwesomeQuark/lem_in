/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:58:02 by bghandou          #+#    #+#             */
/*   Updated: 2019/04/18 14:18:32 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
void	compare_weights(t_node **room, int idx,t_path **vzt_nxt,
		t_path **reinit) //only when node already visited
{
	t_node	*nxt_room;

	nxt_room = (*room)->links[idx];
	if ((*room)->weight + 1 < nxt_room->weight)
	{
		remove_path(nxt_room->hist);
		nxt_room->hist = copy_path(room->hist);
		add_path(nxt_room, nxt_room->hist);
	}
}

void	closed_access_case(t_node **room, t_path **vzt_nxt, int idx, t_path **reinit)
{
	int		i;
	t_node	*nxt_room;

	i = -1;
	nxt_room = (*room)->links[idx];
	while (nxt_room->links[++i])
	{
		if (nxt_room->flux[i] <= 0)
		{
			if(!*vzt_nxt)
				*vzt_nxt = new_path(nxt_room);
			else
				add_path(nxt_room, *vzt_nxt);
			*room = build_path(*room, i);
			nxt_room->weight -= 1;
			nxt_room->vzt = VISITED;
		}
		else if (reverse_flux_case(nxt_room, i)
				&& nxt_room->links[i]->role != START)
		{
	dprintf(1, "PASS!?->%s\n", nxt_room->name);
		//	*room = build_path(*room, i);
		//	nxt_room->weight -= 1;
		}
		*room = build_path(*room, idx);
		nxt_room->weight -= 1;
		nxt_room->vzt = VISITED;
		break;
	}
}*/
