/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_links_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:10:12 by conoel            #+#    #+#             */
/*   Updated: 2019/03/20 16:10:23 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static int		realloc_link_list(t_node *node, t_node *link)
{
	int		nb_links;
	t_node	**tmp;

	nb_links = 0;
	while ((node->links)[nb_links] != NULL)
		nb_links++;
	if (!(tmp = malloc(sizeof(t_node *) * (nb_links + 2))))
		return (return_(NULL));
	nb_links = 0;
	while ((node->links)[nb_links] != NULL)
	{
		tmp[nb_links] = (node->links)[nb_links];
		nb_links++;
	}
	free(node->links);
	tmp[nb_links] = link;
	tmp[nb_links + 1] = NULL;
	node->links = tmp;
	return (1);
}

int				alloc_links_list(t_node *node, t_node *link)
{
	if (!node || !link)
		return (return_("Inexistant node name in links list"));
	if (node->links == NULL)
	{
		if (!(node->links = malloc(sizeof(t_node *) * 2)))
			return (return_(NULL));
		(node->links)[0] = link;
		(node->links)[1] = NULL;
	}
	else if (!(realloc_link_list(node, link)))
		return (0);
	return (1);
}
