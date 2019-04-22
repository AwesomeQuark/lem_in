/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:06 by conoel            #+#    #+#             */
/*   Updated: 2019/04/19 15:58:24 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_links(t_node *node)
{
	int	i;

	i = 0;
	if (node->links == NULL)
		return ;
	while ((node->links)[i] != NULL)
	{
		ft_printf("%8s ", ((node->links)[i])->name);
		i++;
	}
}

void		print_nodes(t_node *head)
{
	while (head != NULL)
	{
		ft_printf("NAME : %8s ROLE : %d ACCSS : %d VZT : %d LINKED TO : ", head->name, head->role, head->access, head->vzt,head->next);
		print_links(head);
		ft_printf("\n");
		head = head->next;
	}
}

int				main(int argc, char **argv)
{
	t_node	*head;
	long	ant_nb;

	if (!(head = load_map(argc, argv, &ant_nb)))
		return ((int)return_("Failed to load the map"));
	if (!(basic_solver(head)))
	{
		free_nodes(head);
		return (return_("No path possible\n"));
	}
	test_function(head);
	display_end(head, ant_nb, argc == 3 ? argv[2] : NULL);
	free_nodes(head);
}
