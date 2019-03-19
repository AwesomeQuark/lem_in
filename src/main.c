/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:06 by conoel            #+#    #+#             */
/*   Updated: 2019/03/19 11:15:26 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static void		print_nodes(t_node *head)
{
	while (head != NULL)
	{
		ft_printf("Name : %-*s Role : %d  Next : %p\n", 8, head->name, head->role, head->next);
		head = head->next;
	}
}

int		main(int argc, char **argv)
{
	t_node	*head;
	int		ant_nb;
	
	if (!(head = load_map(argc, argv, &ant_nb)))
	{
		return((int)return_("Failed to load the map"));
	}
	//ft_printf("Ants quantity : %d\n", ant_nb);
	print_nodes(head);
	free_nodes(head);
}