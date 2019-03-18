/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:52:28 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 16:51:52 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static char			*get_name(char *line)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	line[i] = '\0';
	if (!(ret = ft_strdup(line)))
		return((char *)return_(NULL));
	line[i] = ' ';
	return (ret);
}

static t_node		*new_node(char *line, int role)
{
	t_node	*new;

	if (!(new = malloc(sizeof(t_node))))
		return((t_node *)return_(NULL));
	if (!(new->name = get_name(line)))
		return (NULL);
	new->role = role;
	new->next = NULL;
	return (new);
}

t_node				*add_node(t_node *head, char *line, int role)
{
	t_node	*ptr;
	t_node	*last;

	ptr = head;
	last = NULL;
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
			last = ptr;
		ptr = ptr->next;
	}
	if (!(ptr = new_node(line, role)))
		return (NULL);
	if (head == NULL)
		head = ptr;
	if (last != NULL)
		last->next = ptr;
	return (head);
}