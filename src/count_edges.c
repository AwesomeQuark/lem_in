/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_edges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:32:44 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 15:43:11 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		count_edges(t_node *room)
{
	int		i;

	i = -1;
	if (room->links)
	{
		while (room->links[++i])
			;
	}
	return (i);
}

int		count_iterations(t_node *head)
{
	t_node	*room;
	int		strt;
	int		end;

	room = get_start(head);
	strt = count_edges(room);
	room = get_end(head);
	end = count_edges(room);
	if (end < strt)
		return (end);
	else if (strt <= end)
		return (strt);
	return (0);
}
