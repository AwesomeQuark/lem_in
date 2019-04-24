/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:04:41 by conoel            #+#    #+#             */
/*   Updated: 2019/04/24 20:13:06 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "visu.h"

static void	draw_grid(SDL_Renderer *ren)
{
	int	width;
	int	height;
	int	x;
	int	y;

	x = 0;
	y = 0;
	SDL_GetRendererOutputSize(ren, &width, &height);
	SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
	while (x < width)
	{
		SDL_RenderDrawLine(ren, x, 0, x, height);
		x += SIZE;
	}
	while (y < height)
	{
		SDL_RenderDrawLine(ren, 0, y, height, y);
		y += SIZE;
	}
}

static void	draw_links(t_node *head, SDL_Renderer *ren)
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
			SDL_RenderDrawLine(ren, head->x * SIZE, head->y * SIZE,
				head->links[i]->x * SIZE, head->links[i]->y * SIZE);
			i++;
		}
		head = head->next;
	}
}

void		draw_map(t_node *head, SDL_Renderer *ren)
{
	SDL_Rect	node;

	node.w = SIZE / 2;
	node.h = SIZE / 2;
	while (head)
	{	
		if (head->role == START)
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		else if (head->role == END)
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
		node.x = (head->x * SIZE) - (SIZE / 4);
		node.y = (head->y * SIZE) - (SIZE / 4);
		SDL_RenderDrawRect(ren, &node);
		SDL_RenderFillRect(ren, &node);
		head = head->next;
	}
}

void		draw(t_node *head, SDL_Renderer *ren)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	draw_grid(ren);
	draw_links(head, ren);
	draw_map(head, ren);
	SDL_RenderPresent(ren);
}