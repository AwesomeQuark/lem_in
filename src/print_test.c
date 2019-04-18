/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 21:16:02 by bghandou          #+#    #+#             */
/*   Updated: 2019/04/16 17:18:16 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_path_test(t_path *head)
{
	while (head != NULL)
	{
		ft_printf("room %s wgt %d  --->>    ", head->room->name, head->room->weight);
		head = head->next;
	}
	ft_printf("\n");
}

void		print_path_final(t_path *head)
{
	while (head != NULL)
	{
		ft_printf("|  || |room %s ==>   ", head->room->name);
		head = head->next;
	}
	ft_printf("\n");
}

void	print_flux(t_node *room)
{
	int		i;

	i = -1;
	while(room->links[++i])
	{
		ft_printf("()()Room %s to %s with flux %d()()\n", room->name,
				room->links[i]->name, room->flux[i]);
	}
}
