/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:31:41 by conoel            #+#    #+#             */
/*   Updated: 2019/04/21 17:05:51 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant	*allocate_ants(long ant_nb, t_node *start)
{
	t_ant	*head;
	t_ant	*ptr;
	t_ant	*ptr2;

	if (!(head = malloc(sizeof(t_ant))))
		return (NULL);
	head->room = start;
	head->next = NULL;
	ptr2 = head;
	while (--ant_nb)
	{
		ptr = ptr2;
		if (!(ptr2 = malloc(sizeof(t_ant))))
			return (NULL);
		ptr2->next = NULL;
		ptr2->room = start;
		ptr->next = ptr2;
	}
	return (head);
}

static t_node	*next_path(t_node *current)
{
	int i;

	i = 0;
	if (!current || !current->flux || !current->flux)
		return (NULL);
	while (current->flux[i] != -1)
	{
		if (current->flux[i] == 1)
			return (current->links[i]);
		i++;
	}
	return (NULL);
}

static int	update_ants(t_ant *ants, t_node *start, t_node * end, long *ant_nb)
{
	t_node		*next;
	int			finished;

	finished = 1;
	while (ants != NULL)
	{
		if (ants->room == end && *ant_nb > 0)
		{
			ants->room = start;
		}
		if (ants->room != end && (next = next_path(ants->room))->access == 1)
		{
			finished = 0;
			if (ants->room == start)
				ants->nb = *ant_nb--;
			ft_printf("[L\033[31m%d\033[0m\033[32m%s-%s\033[0m]  ", ants->nb, ants->room->name, next->name);
			ants->room->access = 1;
			ants->room = next;
			ants->room->access = 0;
		}
		ants = ants->next;
	}
	return (finished);
}

int			display_end(t_node *head, long ant_nb, char *opt)
{
	t_ant	*ants;
	t_node	*start;
	t_node	*end;
	int		ant;

	ant = 0;
	start = get_start(head);
	end = get_end(head);
	ants = allocate_ants(ant_nb, start);
	reset_nodes(head);
	while (update_ants(ants, start, end, &ant) == 0)
	{
		write(1,"\n", 1);
	}
}