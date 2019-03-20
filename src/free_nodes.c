/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:48:32 by conoel            #+#    #+#             */
/*   Updated: 2019/03/20 18:19:43 by conoel           ###   ########.fr       */
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
			tmp->links = NULL;
		}
		free(tmp->name);
		tmp->name = NULL;
		free(tmp);
		tmp = NULL;
	}
}
