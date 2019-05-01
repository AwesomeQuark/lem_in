/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:04:41 by conoel            #+#    #+#             */
/*   Updated: 2019/04/30 20:46:53 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "visu.h"

t_node	*next_path_visu(t_node *current, int last)
{
	static int	current_nb = 1;
	int i;
	int	count;

	i = 0;
	if (!current || !current->flux || !current->flux)
		return (NULL);
	current_nb++;
	while (current->links[i])
	{
		if (current->flux[i] == 1)
			count++;
		if (count == current_nb)
			break ;
		i++;
	}
	if (last)
		current_nb = 1;
	return (current->links[i]);
}

static void	draw_ants(t_node *head, t_visu *var)
{
	t_node		*next;
	t_ant		*ants;
	SDL_Rect	ant;
	static int			i = 1;

	ant.w = var->size / 4;
	ant.h = var->size / 4;
	ants = var->ants;
	while (ants)
	{
		if (ants->next)
			next = next_path_visu(ants->room, 1);
		else
			next = next_path_visu(ants->room, 0);
		if (next == NULL)
		{
			ants = ants->next;
			continue ;
		}
		ant.x = (ants->room->x * var->size) + (((next->x - ants->room->x) * var->size * i) / STEP) - var->size / 8;
		ant.y = (ants->room->y * var->size) + (((next->y - ants->room->y) * var->size * i) / STEP) - var->size / 8;
		SDL_SetRenderDrawColor(var->ren, 255, 255, 255, 255);
		SDL_RenderDrawRect(var->ren, &ant);
		SDL_RenderFillRect(var->ren, &ant);
		ants = ants->next;
	}
	if (i == STEP)
		i = 1;
	else
		i++;
}

static void	draw_grid(SDL_Renderer *ren, int size)
{
	int	width;
	int	height;
	int	x;
	int	y;

	x = 0;
	y = 0;
	SDL_GetRendererOutputSize(ren, &width, &height);
	SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
	while (x <= width)
	{
		SDL_RenderDrawLine(ren, x, 0, x, height);
		x += size;
	}
	while (y <= height)
	{
		SDL_RenderDrawLine(ren, 0, y, width, y);
		y += size;
	}
}

static void	draw_links(t_node *head, SDL_Renderer *ren, int size)
{
	int		i;

	while (head)
	{
		i = 0;
		if (!head || !head->links || !head->flux)
		{
			head = head->next;
			continue ;
		}
		while (head->links[i] != NULL)
		{
			SDL_SetRenderDrawColor(ren, 0, 100, 0, 255);
			SDL_RenderDrawLine(ren, head->x * size, head->y * size,
				head->links[i]->x * size, head->links[i]->y * size);
			i++;
		}
		head = head->next;
	}
}

void		draw_map(t_node *head, SDL_Renderer *ren, int size)
{
	SDL_Rect	node;

	node.w = size / 2;
	node.h = size / 2;
	while (head)
	{	
		if (head->role == START)
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		else if (head->role == END)
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
		node.x = (head->x * size) - (size / 4);
		node.y = (head->y * size) - (size / 4);
		SDL_RenderDrawRect(ren, &node);
		SDL_RenderFillRect(ren, &node);
		head = head->next;
	}
}

void		draw(t_node *head, t_visu *var, t_ant *ants_old)
{
	int		i;

	i = 0;
	ants_old = NULL;
	//printf("| x[%d] y[%d] %s|\n", var->ants->room->x, var->ants->room->y, var->ants->room->name);
	while (i++ < STEP)
	{
		SDL_SetRenderDrawColor(var->ren, 0, 0, 0, 255);
		SDL_RenderClear(var->ren);
		draw_grid(var->ren, var->size);
		draw_links(head, var->ren, var->size);
		draw_map(head, var->ren, var->size);
		draw_ants(head, var);
		SDL_RenderPresent(var->ren);
		SDL_Delay(TIME_MOV / STEP);
	}
}
