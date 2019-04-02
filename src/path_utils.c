/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:03:51 by conoel            #+#    #+#             */
/*   Updated: 2019/04/02 17:03:51 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_path	*new_path(t_node *node)
{
	t_path	*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	new->next = NULL;
	new->node = node;
	return (new);
}

int		add_path(t_node *node, t_path *path)
{
	t_path	*new;

	if (!(new = new_path(node)))
		return (0);
	while (path->next != NULL)
		path = path->next;
	path->next = new;
	return (1);
}

void	remove_path(t_path *path)
{
	while (path->next->next != NULL)
		path = path->next;
	free(path->next);
	path->next = NULL;
}
