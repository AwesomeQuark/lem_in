/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:57:55 by conoel            #+#    #+#             */
/*   Updated: 2019/04/22 17:06:05 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"visu.h"

int		sdl_start(SDL_Window **win, SDL_Renderer **ren)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
		return 0;
	}
	if (!(*win = SDL_CreateWindow("Mes couilles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE )))
	{
		printf("Erreur de creation de fenetre de la SDL : %s",SDL_GetError());
		return 0;
	}
	if (!(*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	{
		printf("Erreur de creation de renderer de la SDL : %s",SDL_GetError());
		return 0;
	}
	SDL_SetRenderDrawColor(*ren, 0, 0, 0, 255);
	SDL_RenderClear(*ren);
	SDL_RenderPresent(*ren);
	return (1);
}

void	sdl_end(SDL_Window *win, SDL_Renderer *ren)
{
	SDL_DestroyRenderer(ren); 
	SDL_DestroyWindow(win);
	SDL_Quit();
}