/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:15:00 by conoel            #+#    #+#             */
/*   Updated: 2019/04/22 18:45:23 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

t_node	*load_nodes(t_token *head)
{
	while(head)
	{
		if (head->type == COMM)
		{
			if (head->next && head->next->next)
				head = head->next->next;
			else
				break;
		}
		if (ft_strchr(head->content, '-') == 0 && head->type == MISC_STRING)
			break;
		if (head->next && head->next->next)
		{
			if ()
		}
	}
	return (1);
}