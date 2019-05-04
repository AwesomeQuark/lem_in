/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:29:15 by conoel            #+#    #+#             */
/*   Updated: 2019/05/04 12:27:17 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int					display_end_visu(t_node *head, long ant_nb, int size, int *table)
{
	t_visu		var;

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
		draw(head, &var, table);
		if (update_ants(var.ants, var.start, var.end, ant_nb) == 1)
			break ;
	}
	sdl_end(var.win, var.ren);
	return (1);
}