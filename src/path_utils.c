/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 18:10:40 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 12:51:49 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*new_path(t_node *node)
{
	t_path	*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (node)
		new->room = node;
	else
		new->room = NULL;
	return (new);
}

int		add_path(t_node *node, t_path *path)
{
	t_path	*new;
	t_path	*tmp;

	if (!(new = new_path(node)))
		return (0);
	tmp = NULL;
	while (path->next != NULL)
	{
		tmp = path;
		path = path->next;
	}
	new->prev = path;
	path->next = new;
	return (1);
}

void	remove_path(t_path *path)
{
	t_path	*tmp;

	tmp = NULL;
	while (path->next)
	{
		tmp = path;
		path = path->next;
		free(tmp);
		tmp = NULL;
	}
	if (tmp)
		tmp = NULL;
}

/*
void	remove_path(t_path *path)
{
	if (path->next)
	{
		while (path->next->next != NULL)
			path = path->next;
	}
	free(path->next);
	path->next = NULL;
}
*/
t_path	*copy_path(t_path *path)
{
	t_path	*head;
	t_path	*tmp;
	t_path	*prv;
	t_path	*tmp2;

	tmp = NULL;
	head = NULL;
	prv = NULL;
	tmp2 = NULL;
	while (path)
	{
		if (!(tmp = (t_path*)malloc(sizeof(t_path))))
			return (NULL);
		tmp->room = path->room;
		tmp->next = NULL;
		tmp->prev = NULL;
		if (!head)
		{
			head = tmp;
			prv = head;
			tmp2 = head;
		}
		else
		{
			prv->next = tmp;
			prv = prv->next;
			prv->prev = tmp2;
			tmp2 = tmp;
		}
		path = path->next;
	}
	return (head);
}

t_path	*deprecate_first(t_path **path, t_path *deprecated)
{
	t_path	*tmp;
	t_path	*tmp_dep;

	tmp = *path;
	*path = (*path)->next;
	tmp->next = NULL;
	tmp_dep = deprecated;
	if (!deprecated)
		deprecated = tmp;
	else
	{
		while (tmp_dep->next)
			tmp_dep = tmp_dep->next;
		tmp_dep->next = tmp;
	}
	return (deprecated);
}

void	reinit_visited(t_path **history)
{
	t_path	*tmp;

	tmp = NULL;
	if (*history)
		tmp	= *history;
	while (tmp)
	{
		tmp->room->vzt = FREE;
		tmp->room->skip = 0;
		tmp->room->weight = 0;
		if (tmp->room->hist)
		{
			remove_path(tmp->room->hist);
			tmp->room->hist = NULL;
		}
		tmp = tmp->next;
	}
	free(*history);
	*history = NULL;
}
