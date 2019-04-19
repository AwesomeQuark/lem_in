/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:59 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 17:03:48 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	*nb_paths(t_node *head, int *ant_index)
{
	int	i;
	int	nb;
	int	*ret;

	i = 0;
	nb = 0;
	while (head->flux[i] != -1)
		if (head->flux[i++] == 1)
			nb++;
	ret = malloc(sizeof(int *) * nb);
	i = 0;
	while (i < nb)
	{
		ret[i] = i;
		i++;
	}
	*ant_index = nb - 1;
	return (ret);
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
			list[size--] = start->links[i];
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
	int		ant_index;

	op_count = 0;
	if (!(currents = get_firsts(head)) || !(memory = get_firsts(head)))
		return (return_free(NULL, 1, currents));
	ants = nb_paths(get_start(head), &ant_index);
	while (ant_nb > ant_index)
	{
		i = 0;
		while (currents[i] != NULL)
		{
			ft_printf("L%d-%s ", ants[i] + 1, currents[i]->name);
			if (currents[i] == get_end(head))
			{
				currents[i] = memory[i];
				ants[i] = ++ant_index;
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