/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   travel_flux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:55:44 by bghandou          #+#    #+#             */
/*   Updated: 2019/04/30 19:47:53 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	create_flux(t_node **room)
{
	int		i;

	i = -1;
	while ((*room)->links[++i])
		;
	if (!((*room)->flux = (int*)malloc(sizeof(int) * (i + 1))))
		return ;
	i = -1;
	while ((*room)->links[++i])
		(*room)->flux[i] = 0;
}

int		reverse_flux_case(t_node *room, int idx)
{
	int	 	idx_rvse;
	t_node	*nxt_room;

	nxt_room = room->links[idx];
	idx_rvse = find_index(nxt_room, room);
	if (nxt_room && nxt_room->flux)
	{
		if (nxt_room->flux[idx_rvse] == 1 && nxt_room->role == 0)
			return (1);
	}
	return (0);
}

void	adjust_reverse_flux(t_node **room, int idx)
{
	int	 	idx_rvse;
	t_node	*nxt_room;

	nxt_room = (*room)->links[idx];
	idx_rvse = find_index(nxt_room, *room);
	nxt_room->flux[idx_rvse] = 0;
}

void	test_flux(t_node *room)
{
	int		i;

	i = -1;
	while (room->links[++i])
	{
		if (room->flux)
		{
			if (room->flux[i] == 1 && room->links[i]->tag <= 0)
			{
				ft_printf("room %s to %s\n", room->name, room->links[i]->name);
				if (room->links[i]->role == 0)
					room->links[i]->tag = 1;
				room = room->links[i];
				i = -1;
			}
		}
	}
}

void	flux_or_tag(t_node *start, int actv)
{
	int		i;

	i = -1;
	while (start->links[++i])
	{
		if (start->flux)
		{
			if (start->flux[i] == 1 && start->links[i]->role == 0
					&& actv == -1)
				start->flux[i] = 0;
			if (start->flux[i] == 1 && start->links[i]->tag == 1
					&& start->links[i]->role == 0)
			{
				if (actv <= 0)
					start->links[i]->tag = 0;
				start = start->links[i];
				i = -1;
			}
		}
	}
}
