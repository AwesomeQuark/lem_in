/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:44:42 by bghandou          #+#    #+#             */
/*   Updated: 2019/04/19 14:35:37 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			find_index(t_node *prev, t_node *next)
{
	int		i;

	i = -1;
	while (prev && (prev->links[++i]
				&& ft_strcmp((prev->links[i])->name, next->name)))
		;
	return (i);
}

static void		forward_flux(t_node *start, t_node **room)//travers l'historique
{
	t_node	*path_tmp;
	t_path	*cur_room;
	int		idx;

	cur_room = (*room)->hist;
	path_tmp = cur_room->room;
	idx = 0;
	idx = find_index(start, (*room)->hist->room);
	start->flux[idx] = 1;
	while (cur_room->next)
	{
		path_tmp = cur_room->room;
		path_tmp->access = CLSD;
		path_tmp->vzt = FREE;
		idx = find_index(path_tmp, cur_room->next->room);
		if (reverse_flux_case(path_tmp, idx))
			adjust_reverse_flux(&path_tmp, idx);
		else
			path_tmp->flux[idx] = 1;
		cur_room = cur_room->next;
	}
	cur_room->room->access = CLSD;
}

void	shortest_path(t_node **room, t_node *head)
{
	t_node	*start;

	start = get_start(head);
	ft_printf("==========================\n");
	print_path_final((*room)->hist);
	ft_printf("==========================\n");
	forward_flux(start, room);
}
