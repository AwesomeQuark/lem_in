/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:29:15 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 17:22:31 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		update_ants_visu(t_ant *ants, t_node *start, t_node *end, long ant_nb)
{
	static long	next_ant_index = 0;
	t_node		*next;
	int			finished;

	finished = 1;
	while (ants != NULL)
	{
		if (ants->room == end && ant_nb > next_ant_index)
		{
			ants->room = start;
			ants->nb = ++next_ant_index;
		}
		if (ants->room != end && (next = next_path(ants->room)))
		{
			finished = 0;
			ants->room->access = 1;
			ants->room = next;
			if (next != end)
				ants->room->access = 0;
		}
		ants = ants->next;
	}
	return (finished);
}

int					display_end_visu(t_node *head, long ant_nb, int size)
{
	t_visu		var;
	SDL_Event	e;

	var.ant = 0;
	var.size = size != 0 ? size : SIZE;
	var.start = get_start(head);
	var.end = get_end(head);
	if (!(sdl_start(&var, width_map(head), height_map(head))))
		return (0);
	reset_nodes(head);
	if (!(var.ants = allocate_ants(ant_nb, var.end)))
		return (0);
	while (1)
	{
		draw(head, &var);
		if (update_ants_visu(var.ants, var.start, var.end, ant_nb) == 1)
			break ;
	}
	sdl_end(var.win, var.ren);
	return (1);
}