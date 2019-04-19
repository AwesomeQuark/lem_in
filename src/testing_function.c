/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:10:46 by bghandou          #+#    #+#             */
/*   Updated: 2019/04/19 14:36:39 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*visit_paths(t_node **room, t_path **vzt_nxt, t_path *reinit)//use ft_ to find leaking  deprecated paths
{
//	if (*vzt_nxt) // might not need
//	{
		*room = (*vzt_nxt)->room;
		reinit = deprecate_first(vzt_nxt, reinit);
//	}
	return (reinit);
}

void	flux_to_end(t_node **room, t_path **vzt_nxt, int i, t_node *head)
{
	if (((*room)->links[i])->role == END && (*room)->flux[i] == 0)//put this condition before function start
	{
		ft_printf("done to END: %s\n", (*room)->name);
		(*room)->flux[i] = 1;
		shortest_path(room, head);
		while (*vzt_nxt && (*vzt_nxt)->room->role != END)
		{
			(*vzt_nxt)->room->vzt = FREE; // take care of overflow of vzt_nxt
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
			//ft_printf("INROOM:%s__i:%d))targeting:%s...visit:%d\n", room->name, i, (room->links[i])->name, room->links[i]->vzt);
			}
	}
	else
	{
			if ((room->links[i])->role == 0 && (room->links[i])->vzt == FREE)
			{
	//		ft_printf("2.INROOM:%s__i:%d))targeting:%s...visit:%d\n", room->name, i, (room->links[i])->name, room->links[i]->vzt);
				room->links[i]->weight = room->weight + 1;
				(room->links[i])->hist = copy_path(room->hist);
				add_path(room->links[i], (room->links[i])->hist);
			}
	//	free(room->hist);
	}
	return (room);
}

void	closed_access_case(t_node **room, t_path **vzt_nxt, int idx, t_path **reinit)
{
	t_node *nxt_room;
	int		i;

	reinit = (t_path **)reinit;
	i = -1;
	nxt_room = (*room)->links[idx];
//				dprintf(1, "*ROOM: %s poiting to : %s\n", (*room)->name, nxt_room->name);
	if ((*room)->flux[idx] <= 0)
	{
		while (nxt_room->links[++i])
		{
//	dprintf(1, "*room_nxt is: %s and aiming to %s with flux: %d\n", nxt_room->name, nxt_room->links[i]->name, nxt_room->flux[i]);
			if (reverse_flux_case(nxt_room, i))
			{
//			ft_printf("*****CONDITIONS ROOM ADD: %s....pointing to :%s__%s\n", nxt_room->name, nxt_room->links[i]->name, (*room)->name);
				if (!*vzt_nxt)
				{
					*vzt_nxt = new_path(nxt_room);
					add_path(nxt_room->links[i], *vzt_nxt); //too much?
				}
				else
				{
					add_path(nxt_room,*vzt_nxt);
					add_path(nxt_room->links[i], *vzt_nxt);//maybe too much to skip2 
				}
				*room = build_path(*room, idx);
				nxt_room = build_path(nxt_room, i);
				nxt_room->weight -= 1;
				nxt_room->vzt = VISITED;
				nxt_room->links[i]->vzt = VISITED; //too much?
				nxt_room->skip = 1;
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
		//	room = build_path(room, i);
			//if (room->links[i]->access == CLSD && room->flux[i] <= 0)
			//	closed_access_case(&room, &vzt_nxt, i, &reinit);
			room->skip = 0;
			break ; 
		}
//			ft_printf("'''INROOM:%s__i:%d))targeting:%s...visit:%d\n", room->name, i, (room->links[i])->name, room->links[i]->vzt);
		if ((room->links[i])->vzt == FREE /*&& room->access == OPEN/test*/ && (room->links[i])->role != START
				&& ((room->flux[i] <= 0 && room->links[i]->access == OPEN)
				/*|| (reverse_flux_case(room, i) && room->links[i]->access == CLSD)*/)) // might not need condition after last "||"
		{
			ft_printf("FIRST CONDITIONS ROOM ADD: %s\n", room->links[i]->name);
			if (!vzt_nxt)
				vzt_nxt = new_path(room->links[i]);
			else
				add_path(room->links[i], vzt_nxt);
			room = build_path(room, i);
			(room->links[i])->vzt = VISITED;
		}
		if (room->links[i]->access == CLSD/* && room->links[i]->vzt == FREE*/)//add condition for when room im in is CLSD!
			closed_access_case(&room, &vzt_nxt, i, &reinit); // this whole condition might be wrong, only here for testing
		flux_to_end(&room, &vzt_nxt, i, head);
	}
	return (vzt_nxt);
}


void	test_function(t_node *head)
{
	t_path	*vzt_nxt;
	t_node	*room;
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
			print_path_test(vzt_nxt);//
			if ((vzt_nxt && vzt_nxt->room->role == END)/*|| !vzt_nxt*/) //might not need thislast part of condition after "||"
				break ;
			//room = build_path(room);
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
