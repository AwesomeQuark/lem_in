/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:29:15 by conoel            #+#    #+#             */
/*   Updated: 2019/04/23 18:30:31 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int			sdl_start(SDL_Window **win, SDL_Renderer **ren)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
		return (0);
	}
	if (!(*win = SDL_CreateWindow("Mes couilles", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN)))
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

void		draw(t_node *head, SDL_Renderer *ren, int factor)
{
	draw_map(head, ren, factor);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderPresent(ren);
}

void		sdl_end(SDL_Window *win, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
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
	}
	sdl_end(var.win, var.ren);
	return (1);
}
