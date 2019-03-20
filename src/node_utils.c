/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:16:08 by conoel            #+#    #+#             */
/*   Updated: 2019/03/20 16:21:06 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_node			*get_node(char *name, size_t len, t_node *head)
{
	size_t		len2;

	while (head != NULL)
	{
		len2 = ft_strlen(head->name);
		if (len == len2)
			if (ft_memcmp(head->name, name, len) == 0)
				return (head);
		head = head->next;
	}
	return (NULL);
}

t_node			*get_start(t_node *head)
{
	if (head == NULL)
		return (NULL);
	while (head->role != 1 && head)
	{
		head = head->next;
	}
	if (head)
		return (head);
	return (NULL);
}

t_node			*get_end(t_node *head)
{
	if (head == NULL)
		return (NULL);
	while (head->role != 2 && head)
	{
		head = head->next;
	}
	if (head)
		return (head);
	return (NULL);
}

t_node			*get_next_open_link(t_node *node)
{
	int		i;

	i = 0;
	if (node == NULL)
		return (NULL);
	while (node->links[i]->access == 0 && node->links[i]->access)
		i++;
	return (node->links[i]);
}