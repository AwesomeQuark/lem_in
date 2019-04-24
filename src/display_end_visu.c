/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:29:15 by conoel            #+#    #+#             */
/*   Updated: 2019/04/24 20:05:36 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int			width_map(t_node *head)
{
	t_node	*ptr;
	int 	max;
	int		min;

	max = 0;
	min = head->x;
	ptr = head;
	while (ptr)
	{
		if (ptr->x < min)
			min = ptr->x;
		ptr = ptr->next;
	}
	ptr = head;
	while (ptr)
	{
		ptr->x -= min - 1;
		if (ptr->x > max)
			max = ptr->x;
		ptr = ptr->next;
	}
	printf("WIDTH (X) : min[%d] max[%d]", min, max);
	return (max + 1);
}

static int			height_map(t_node *head)
{
	t_node	*ptr;
	int 	max;
	int		min;

	max = 0;
	min = head->y;
	ptr = head;
	while (ptr)
	{
		if (ptr->y < min)
			min = ptr->y;
		ptr = ptr->next;
	}
	ptr = head;
	while (ptr)
	{
		ptr->y -= min - 1;
		if (ptr->y > max)
			max = ptr->y;
		ptr = ptr->next;
	}
	printf("HEIGHT (Y) : min[%d] max[%d]", min, max);
	return (max + 1);
}

static int			sdl_start(SDL_Window **win, SDL_Renderer **ren, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
		return (0);
	}
	if (!(*win = SDL_CreateWindow("Mes couilles", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width * SIZE, height * SIZE, SDL_WINDOW_SHOWN)))
	{
		printf("Erreur de creation de fenetre de la SDL : %s", SDL_GetError());
		return (0);
	}
	if (!(*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC)))
	{
		printf("Erreur de creation de renderer de la SDL : %s", SDL_GetError());
		return (0);
	}
	SDL_SetRenderDrawColor(*ren, 255, 255, 255, 255);
	SDL_RenderClear(*ren);
	SDL_RenderPresent(*ren);
	SDL_PumpEvents();
	return (1);
}

static void		sdl_end(SDL_Window *win, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

int				display_end_visu(t_node *head, long ant_nb)
{
	t_visu		var;
	SDL_Event	e;

	var.ant = 0;
	var.start = get_start(head);
	var.end = get_end(head);
	sdl_start(&var.win, &var.ren, width_map(head), height_map(head));
	reset_nodes(head);
	if (!(var.ants = allocate_ants(ant_nb, var.end)))
		return (0);
	while (1)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.button.button == SDL_BUTTON_LEFT)
				draw(head, var.ren);
			if (e.button.button == SDL_BUTTON_RIGHT)
				break ;
		}
		SDL_Delay(20);
	}
	sdl_end(var.win, var.ren);
	return (1);
}