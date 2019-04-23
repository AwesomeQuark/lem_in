/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:52:28 by conoel            #+#    #+#             */
/*   Updated: 2019/04/23 16:57:50 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			get_coord(char *line, int *x, int *y)
{
	size_t	i;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	*x = ft_strtoll(&line[i], &i, 10);
	*y = ft_strtoll(&line[i], &i, 10);
}

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
	{
		free(ret);
		return ((char *)return_("Forbidden char in room name (L or -)"));
	}
	return (ret);
}

static t_node		*new_node(char *line, int role)
{
	t_node	*new;

	if (!(new = malloc(sizeof(t_node))))
		return ((t_node *)return_(NULL));
	if (!(new->name = get_name(line)))
		return (NULL);
	get_coord(line, &new->x, &new->y);
	new->role = role;
	new->hist = NULL;
	new->next = NULL;
	new->links = NULL;
	new->access = OPEN;
	new->vzt = FREE;
	new->flux = NULL;
	new->skip = 0;
	new->weight = 0;
	new->printed = 0;
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
