/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:18:13 by conoel            #+#    #+#             */
/*   Updated: 2019/05/22 18:13:17 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		width_map(t_node *head)
{
	t_node	*ptr;
	int		max;
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
	return (max + 1);
}

int		height_map(t_node *head)
{
	t_node	*ptr;
	int		max;
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
	return (max + 1);
}

int		sdl_start(t_visu *var, int width, int height)
{
	if (width * var->size > MAX_WIDTH
		|| height * var->size > MAX_HEIGHT)
		return (return_("Cannot create the window, too large map !"));
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		ft_printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
		return (0);
	}
	if (!(var->win = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width * var->size, height * var->size,
		SDL_WINDOW_SHOWN)))
	{
		ft_printf("Erreur de creation de fenetre : %s", SDL_GetError());
		return (0);
	}
	if (!(var->ren = SDL_CreateRenderer(var->win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC)))
	{
		ft_printf("Erreur de creation de renderer : %s", SDL_GetError());
		return (0);
	}
	SDL_SetRenderDrawColor(var->ren, 255, 255, 255, 255);
	SDL_RenderClear(var->ren);
	SDL_RenderPresent(var->ren);
	SDL_PumpEvents();
	return (1);
}

void	sdl_end(SDL_Window *win, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
