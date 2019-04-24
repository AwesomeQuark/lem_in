/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:31:41 by conoel            #+#    #+#             */
/*   Updated: 2019/04/23 16:50:43 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu.h"

static t_ant	*allocate_ants(long ant_nb, t_node *end)
{
	t_ant	*head;
	t_ant	*ptr;
	t_ant	*ptr2;

	if (!(head = malloc(sizeof(t_ant))))
		return (NULL);
	head->room = end;
	head->next = NULL;
	ptr2 = head;
	while (--ant_nb)
	{
		ptr = ptr2;
		if (!(ptr2 = malloc(sizeof(t_ant))))
			return (NULL);
		ptr2->next = NULL;
		ptr2->room = end;
		ptr->next = ptr2;
	}
	return (head);
}

static t_node	*next_path(t_node *current)
{
	int i;

	i = 0;
	if (!current || !current->flux || !current->flux)
		return (NULL);
	while (current->links[i])
	{
		if (current->flux[i] == 1 && current->links[i]->access == 1)
			return (current->links[i]);
		i++;
	}
	return (NULL);
}

static int		update_ants(t_ant *ants, t_node *start, t_node *end
	, long ant_nb)
{
	static long	next_ant_index = 0;
	t_node		*next;
	int			finished;

	finished = 1;
	while (ants != NULL)
	{
		if (ants->room == end && ant_nb > next_ant_index)
		{
			ants->room = start;
			ants->nb = ++next_ant_index;
		}
		if (ants->room != end && (next = next_path(ants->room)))
		{
			finished = 0;
			ft_printf("L%d-%s ", ants->nb, next->name);
			ants->room->access = 1;
			ants->room = next;
			if (next != end)
				ants->room->access = 0;
		}
		ants = ants->next;
	}
	return (finished);
}

int				display_end(t_node *head, long ant_nb)
{
	t_ant	*ants;
	t_node	*start;
	t_node	*end;
	int		ant;

	ant = 0;
	start = get_start(head);
	end = get_end(head);
	reset_nodes(head);
	if (!(ants = allocate_ants(ant_nb, end)))
		return (0);
	while (update_ants(ants, start, end, ant_nb) == 0)
	{
		write(1, "\n", 1);
	}
	return (1);
}

int				display_end_visu(t_node *head, long ant_nb, int factor)
{
	t_visu		var;
	SDL_Event	e;

	var.ant = 0;
	var.start = get_start(head);
	var.end = get_end(head);
	sdl_start(&var.win, &var.ren);
	reset_nodes(head);
	if (!(var.ants = allocate_ants(ant_nb, var.end)))
		return (0);
	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.button.button == SDL_BUTTON_LEFT)
				draw(head, var.ren, factor);
			if (e.button.button == SDL_BUTTON_RIGHT)
				break ;
		}
		SDL_Delay(20);
	}
	sdl_end(var.win, var.ren);
	return (1);
}
