/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:48:32 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 16:50:39 by conoel           ###   ########.fr       */
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
		free(tmp->name);
		free(tmp);
	}
}