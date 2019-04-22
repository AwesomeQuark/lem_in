/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:41:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/04/22 08:16:19 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_path	*visit_paths(t_node **room, t_path **vzt_nxt, t_path *reinit)//use ft_ to find leaking  deprecated paths
{
	if (!*vzt_nxt)
		return (reinit);
	else
		*room = (*vzt_nxt)->room;
	reinit = deprecate_first(vzt_nxt, reinit);
	return (reinit);
}

void	flux_to_end(t_node **room, t_path **vzt_nxt, int i, t_node *head)
{
	if (((*room)->links[i])->role == END && (*room)->flux[i] == 0)
	{
		(*room)->flux[i] = 1;
		shortest_path(room, i, head);
		while (*vzt_nxt && (*vzt_nxt)->room->role != END)
		{
			(*vzt_nxt)->room->vzt = FREE;
			(*vzt_nxt) = (*vzt_nxt)->next;
		}
	}
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
				(room->links[i])->hist = copy_path(room->hist);
				add_path(room->links[i], (room->links[i])->hist);
			}
	}
	return (room);
}

void	closed_access_case(t_node **room, t_path **vzt_nxt, int idx, t_path **reinit)
{
	t_node *nxt_room;
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
			if (reverse_flux_case(nxt_room, i) 
					&& nxt_room->links[i]->vzt == FREE)
			{
				if (!*vzt_nxt)
				{
					*vzt_nxt = new_path(nxt_room);
					add_path(nxt_room->links[i], *vzt_nxt);
				}
				else
				{
					if (nxt_room->vzt == FREE && !check_outwardflux(room) && !reverse_flux_case(nxt_room, i))
						add_path(nxt_room,*vzt_nxt);
					add_path(nxt_room->links[i], *vzt_nxt);
				}
				*room = build_path(*room, idx);
				nxt_room = build_path(nxt_room, i);
				if ((*room)->access == OPEN)
					nxt_room->weight = (*room)->weight + 1;
				nxt_room->vzt = VISITED;
				nxt_room->links[i]->vzt = VISITED;
				if (nxt_room->links[i]->access == CLSD)
				{
					nxt_room->links[i]->weight = nxt_room->weight - 1;
					closed_access_case(&nxt_room, vzt_nxt, i, reinit);
				}
				break  ;
			}
		}
	}
}

t_path	*build_future(t_node *room, t_path *vzt_nxt, t_node *head, t_path *reinit)
{
	int		i;

	i = -1;
	if (!room->flux)
		create_flux(&room);
	while (room->links[++i])
	{
		if  (room->skip == 1)
		{
			room->skip = 0;
			room->vzt = 0;
			break ; 
		}
		if (room->access == CLSD && room->links[i]->access == OPEN
				&& room->flux[i] <= 0)
		{
			if (skip_from_close(&room, i))
				;
		}
		if (room->links[i]->access == CLSD && room->role != START)
		{
			closed_access_case(&room, &vzt_nxt, i, &reinit);
		}
		else if ((room->links[i])->vzt == FREE && (room->links[i])->role != START
				&& ((room->flux[i] <= 0 && room->links[i]->access == OPEN)))
		{
			if (!vzt_nxt)
				vzt_nxt = new_path(room->links[i]);
			else
				add_path(room->links[i], vzt_nxt);
			room = build_path(room, i);
			(room->links[i])->vzt = VISITED;
		}
		flux_to_end(&room, &vzt_nxt, i, head);
	}
	return (vzt_nxt);
}


void	test_function(t_node *head)
{
	t_path	*vzt_nxt;
	t_node	*room;
	t_node	*start;
	t_path	*reinit;
	int		loops;

	vzt_nxt = NULL;
	reinit = NULL;
	loops = count_iterations(head);
	while (loops > 0)
	{
		room = get_start(head);
		while (1)
		{
			vzt_nxt = build_future(room, vzt_nxt, head, reinit);
			print_path_test(vzt_nxt);
			if (vzt_nxt && vzt_nxt->room->role == END)
				break ;
			if (!vzt_nxt)
				break;
			reinit = visit_paths(&room, &vzt_nxt, reinit);
		}
		reinit_visited(&reinit);
		reinit_visited(&vzt_nxt);
		vzt_nxt = NULL;
		loops--;
	}
	int		test = -1;
	room = get_start(head);
	while(room->links[++test])
	{
		ft_printf("------\n");
		test_flux(room);
		ft_printf("------\n");
	}
	//print_nodes(head);
	//now adjust relative to n_loops and find correct path again
}
