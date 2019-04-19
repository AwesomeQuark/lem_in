/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:59 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 16:36:53 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	nb_paths(t_node *head)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (head->flux[i] != -1)
		if (head->flux[i++] == 1)
			nb++;
	return (nb);
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
		{
			current->links[i]->access = current->access;
			return (current->links[i]);
		}
		i++;
	}
	return (NULL);
}

static t_node	**get_firsts(t_node *head)
{
	t_node **list;
	t_node *start;
	int size;
	int	i;

	i = 0;
	size = 0;
	if (!head || !(start = get_start(head)))
		return (NULL);
	while (start->flux[i] != -1)
		start->flux[i++] == 1 ? size++ : 0;
	if (!(list = malloc(sizeof(t_node *) * (size + 1))))
		return (NULL);
	list[size--] = NULL;
	i = 0;
	while (start->flux[i] != -1)
	{
		if (start->flux[i] == 1)
		{
			list[size] = start->links[i];
			start->links[i]->access = size--;
		}
		i++;
	}
	return (list);
}

int		display_end(t_node *head, long ant_nb, char *opt)
{
	t_node	**currents;
	t_node	**memory;
	int		i;
	int		op_count;
	int		*ants;

	op_count = 0;
	if (!(currents = get_firsts(head)) || !(memory = get_firsts(head)))
		return (return_free(NULL, 1, currents));
	ant = nb_paths(get_start(head));
	while (ant_nb > ant)
	{
		i = 0;
		while (currents[i] != NULL)
		{
			ft_printf("L%d-%s ", currents[i]->access, currents[i]->name);
			if (currents[i] == get_end(head))
			{
				currents[i] = memory[i];
				currents[i]->access = ant;
				ant++;
			}
			else if (!(currents[i] = next_path(currents[i])))
				return (return_free(NULL, 2, currents, memory));
			i++;
		}
		op_count++;
		ft_printf("\n");
	}
	if (ft_memcmp(opt, "-c", 3) == 0)
		ft_printf("Total operations : %s%d%s\n", RED, op_count, DEF);
	free(memory);
	free(currents);
	return (1);
}