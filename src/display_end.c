/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:31:41 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 16:38:08 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu.h"

int	remaining_space(int *table, t_node *start, int mode)
{
	int		i;
	int		j;

	i = 0;
	j = 0;	
	while (start->links[i])
	{
		if (table[j] != 0 && start->links[i]->access == 1 && start->flux[i] == 1)
		{
			if (mode == 1)
				table[j]--;
			return (i);
		}
		if (start->flux[i] == 1)
			j++;
		i++;
	}
	return (-1);
}

t_ant	*allocate_ants(long ant_nb, t_node *end)
{
	t_ant	*head;
	t_ant	*ptr;
	t_ant	*ptr2;

	srand(time(NULL));
	if (!(head = malloc(sizeof(t_ant))))
		return (NULL);
	head->room = end;
	head->next = NULL;
	head->color = rand();
	ptr2 = head;
	while (--ant_nb)
	{
		ptr = ptr2;
		if (!(ptr2 = malloc(sizeof(t_ant))))
			return (NULL);
		ptr2->next = NULL;
		ptr2->room = end;
		ptr2->color = rand();
		ptr->next = ptr2;
	}
	return (head);
}

t_node	*next_path(t_node *current)
{
	int i;

	i = 0;
	if (current->role == END)
		return (NULL);
	while (current->links[i])
	{
		if (current->links[i]->role == END)
			return (current->links[i]);
		if (current->flux[i] == 1 && current->links[i]->access == 1)
			return (current->links[i]);
		i++;
	}
	return (NULL);
}

int		update_ants(t_ant *ants, t_node *head, int *table)
{
	static long	next_ant_index = 0;
	t_node		*next;
	int			finished;
	t_node		*start;
	t_node		*end;

	finished = 1;
	end = get_end(head);
	start = get_start(head);
	while (ants)
	{
		if (ants->room == end && remaining_space(table, start, 0) != -1)
		{
			finished = 0;
			ants->room = start;
			ants->nb = ++next_ant_index;
		}
		if (ants->room != end && (ants->room != start || remaining_space(table, start, 0) != -1)
		&& next_path(ants->room))
		{
			finished = 0;
			if (ants->room == start && start->access == 1)
				next = ants->room->links[remaining_space(table, start, 1)];
			else
				next = next_path(ants->room);
			ft_printf("L", ants->nb, next->name);
			ants->room->access = 1;
			ants->room = next;
			if (next != end)
				ants->room->access = 0;
		}
		ants = ants->next;
	}
	return (finished);
}

int				display_end(t_node *head, long ant_nb, int *table)
{
	t_ant	*ants;
	int		ant;
	int		count;

	ant = 0;
	count = 0;
	reset_nodes(head);
	if (table == NULL)
		return (0);
	else if (table == NULL)
	{
		if (!(table = malloc(sizeof(int) * 1)))
			return (0);
		table[0] = ant_nb;
	}
	if (!(ants = allocate_ants(ant_nb, get_end(head))))
		return (0);
	while (update_ants(ants, head, table) == 0)
	{
		write(1, "\n", 1);
		count++;
	}
	printf("FINAL |%d", count);
	free_ants(ants);
	return (1);
}
