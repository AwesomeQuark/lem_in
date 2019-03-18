/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:48:32 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 18:39:02 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	free_nodes(t_node *head)
{
	t_node	*tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->links != NULL)
		{
			free(tmp->links);
		}
		free(tmp->name);
		free(tmp);
	}
}