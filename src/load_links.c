/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:46:28 by conoel            #+#    #+#             */
/*   Updated: 2019/05/22 16:00:20 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	if_comm(char *data, size_t i, size_t j, t_node *head)
{
	size_t	k;

	k = 0;
	while (data[i + k] != '-' && data[i + k])
		k++;
	if (is_linked(get_node(&(data[i]), k, head), get_node(&(data[i + k
		+ 1]), j - (k + 1), head)))
		if (!(create_link(get_node(&(data[i]), k, head),
			get_node(&(data[i + k + 1]), j - (k + 1), head))))
			return (0);
	return (1);
}

int			is_linked(t_node *node, t_node *node2)
{
	int	i;

	i = 0;
	if (!node->links || !node2->links)
		return (1);
	while (node->links[i])
	{
		if (node->links[i] == node2)
			return (0);
		i++;
	}
	i = 0;
	while (node2->links[i])
	{
		if (node2->links[i] == node)
			return (0);
		i++;
	}
	return (1);
}

int			create_link(t_node *node1, t_node *node2)
{
	if (node1 == node2)
		return (return_("Link between same room"));
	if (!(alloc_links_list(node1, node2)))
		return (0);
	if (!(alloc_links_list(node2, node1)))
		return (0);
	return (1);
}

int			load_links(t_node *head, char *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i + j] != '\n' && data[i + j])
			j++;
		if (ft_memchr(&data[i], '-', j) == NULL && data[i] != '#')
			return (return_("Bad character in the links list\n"));
		if (data[i] != '#')
			if (!(if_comm(data, i, j, head)))
				return (0);
		i += j + 1;
	}
	return (1);
}
