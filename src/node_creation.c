/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:52:28 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 14:35:37 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char			*get_name(char *name)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (name[i] != ' ' && name[i])
		i++;
	name[i] = '\0';
	if (!(ret = ft_strdup(name)))
		return ((char *)return_(NULL));
	name[i] = ' ';
	if (ft_strchr(ret, 'L') != NULL || ft_strchr(ret, '-') != NULL)
		return ((char *)return_("Forbidden char in room name (L or -)"));
	return (ret);
}

static t_node		*new_node(char *name, int role)
{
	t_node	*new;

	if (!(new = malloc_garbage(sizeof(t_node))))
		return ((t_node *)return_(NULL));
	new->links = NULL;
	new->next = NULL;
	new->hist = NULL;
	if (!(new->name = get_name(name)))
		return (NULL);
	new->role = role;
	new->access = 1;
	new->vzt = 0;
	new->flux = NULL;
	new->weight = 0;
	new->printed = 0;
	new->skip = 0;
	return (new);
}

t_node				*add_node(t_node *head, char *name, int role)
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
	if (!(ptr = new_node(name, role)))
		return (NULL);
	if (head == NULL)
		head = ptr;
	if (last != NULL)
		last->next = ptr;
	return (head);
}
