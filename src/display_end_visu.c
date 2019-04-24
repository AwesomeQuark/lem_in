/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:29:15 by conoel            #+#    #+#             */
/*   Updated: 2019/04/23 16:57:30 by conoel           ###   ########.fr       */
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

static void	draw_links(t_node *current, SDL_Renderer *ren, int factor)
{
	int		i;

	i = 0;
	if (!current || !current->links || !current->flux)
		return ;
	while (current->links[i] != NULL)
	{
		if (current->flux[i] == 1)
			SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(ren, 0, 100, 0, 255);
		SDL_RenderDrawLine(ren, (current->x * factor) + (SIZE / 2),
			(current->y * factor) + (SIZE / 2), (current->links[i]->x * factor)
			+ (SIZE / 2), (current->links[i]->y * factor) + (SIZE / 2));
		i++;
	}
}

void		draw_map(t_node *head, SDL_Renderer *ren, int factor)
{
	SDL_Rect	node;

	node.w = SIZE;
	node.h = SIZE;
	while (head)
	{
		if (head->role == 0)
			SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
		if (head->role == START)
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		if (head->role == END)
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		node.x = head->x * factor;
		node.y = head->y * factor;
		SDL_RenderDrawRect(ren, &node);
		SDL_RenderFillRect(ren, &node);
		draw_links(head, ren, factor);
		head = head->next;
	}
	SDL_RenderPresent(ren);
	SDL_Delay(5000);
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
