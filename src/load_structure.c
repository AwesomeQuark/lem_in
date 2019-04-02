/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:41:17 by conoel            #+#    #+#             */
/*   Updated: 2019/04/02 16:54:58 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static int		determine_node_role(char *data, size_t *i, t_node *head, int pos)
{
	if (ft_memcmp(&data[*i], "##start\n", 8) == 0)
		pos = 1;
	else if (ft_memcmp(&data[*i], "##end\n", 6) == 0)
		pos = 2;
	while (head && pos != 0)
	{
		if (head->role == pos)
			return (-1);
		head = head->next;
	}
	return (pos);
}

static t_node	*load_nodes(char *data, size_t *i)
{
	t_node	*head;
	size_t	j;
	int		pos;

	head = NULL;
	pos = 0;
	while (data[*i])
	{
		j = 0;
		while (data[*i + j] != '\n' && data[*i + j])
			j++;
		if (ft_memchr(&data[*i], ' ', j) == NULL && data[*i] != '#')
			break ;
		if ((pos = determine_node_role(data, i, head, pos)) == -1)
		{
			free_nodes(head);
			return ((t_node *)return_("Duplicated start or end"));
		}
		if (data[*i] != '#')
		{
			if (!(head = add_node(head, &data[*i], pos)))
				return (NULL);
			pos = 0;
		}
		*i = *i + j + 1;
	}
	return (head);
}

static int		create_link(t_node *node1, t_node *node2)
{
	if (node1 == node2)
		return (return_("Link between same room"));
	if (!(alloc_links_list(node1, node2)))
		return (0);
	if (!(alloc_links_list(node2, node1)))
		return (0);
	return (1);
}

static int		load_links(t_node *head, char *data)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i + j] != '\n' && data[i + j])
			j++;
		if (ft_memchr(&data[i], '-', j) == NULL && data[i] != '#')
			return (return_("Bad character in the links list\n"));
		if (data[i] != '#')
		{
			k = 0;
			while (data[i + k] != '-' && data[i + k])
				k++;
			if (!(create_link(get_node(&(data[i]), k, head),
					get_node(&(data[i + k + 1]), j - (k + 1), head))))
				return (0);
		}
		i = i + j + 1;
	}
	return (1);
}


t_node			*load_structure(char *data, long *ant_nb)
{
	size_t	i;
	t_node	*head;

	i = 0;
	while (data[i] == '#')
	{
		while (data[i] != '\n' && data[i])
			i++;
		i++;
	}
	*ant_nb = ft_strtoll(&data[i], &i, 10);
	if (*ant_nb < 0)
		return ((t_node *)return_("Negative ant quantity"));
	i++;
	if (!(head = load_nodes(data, &i)))
		return ((t_node *)return_("Failed to load nodes"));
	if (!(load_links(head, &data[i])))
	{
		free_nodes(head);
		return ((t_node *)return_("Failed to load links"));
	}
	if (get_end(head) == NULL || get_start(head) == NULL)
	{
		free_nodes(head);
		return((t_node *)return_("End or start missing"));
	}
	return (head);
}
