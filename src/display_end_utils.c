/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:32:38 by conoel            #+#    #+#             */
/*   Updated: 2019/05/21 18:35:17 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu.h"

int		remaining_space(int *table, t_node *start, int mode)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (start->links[i])
	{
		if (table[j] != 0 && start->links[i]->access == 1
			&& start->flux[i] == 1)
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
