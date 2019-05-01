/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:44:42 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 18:05:53 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_index(t_node *prev, t_node *next)
{
	int		i;

	i = -1;
	while (prev && (prev->links[++i]
				&& ft_strcmp((prev->links[i])->name, next->name)))
		;
	return (i);
}

void	forward_flux(t_node *start, t_node **room)
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

void	start_end(t_node **room)
{
	int		i;

	i = -1;
	while ((*room)->links[++i]->role != END)
		;
	if ((*room)->links[i]->role == END)
		(*room)->flux[i] = 1;
}

void	shortest_path(t_node **room, t_node *head)
{
	t_node	*start;

	if ((*room)->role == START)
	{
		start_end(room);
		return ;
	}
	dprintf(1, "======================\n");
	print_path_final((*room)->hist);
	dprintf(1, "======================\n");
	start = get_start(head);
	forward_flux(start, room);
}
