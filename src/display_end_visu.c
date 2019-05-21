/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:29:15 by conoel            #+#    #+#             */
/*   Updated: 2019/05/21 17:33:59 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		flux_value(t_node *node, char *name)
{
	int	i;

	i = 0;
	while (node->links[i])
	{
		if (ft_strcmp(node->links[i]->name, name) == 0)
			return (node->flux[i]);
		i++;
	}
	return (0);
}

void	free_ants(t_ant *head)
{
	t_ant	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

int		display_end_visu(t_node *head, long ant_nb, int *table,
	int options)
{
	t_visu		var;
	int			count;

	var.ant = 0;
	count = 0;
	var.size = SIZE;
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
		count++;
		if (update_ants(var.ants, head, table, options) == 1)
			break ;
		write(1, "\n", 1);
	}
	if (options & COUNT)
		ft_printf("\n%sFINAL%s : %d\n", RED, DEF, count);
	sdl_end(var.win, var.ren);
	return (1);
}
