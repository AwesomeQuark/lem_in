/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:18:33 by conoel            #+#    #+#             */
/*   Updated: 2019/04/23 18:29:53 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_nodes(t_node *current, SDL_Renderer *ren, int factor)
{
	SDL_Rect	node;

	node.w = SIZE;
	node.h = SIZE;
	if (current->role == 0)
		SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
	if (current->role == START)
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	if (current->role == END)
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	node.x = current->x * factor;
	node.y = current->y * factor;
	SDL_RenderFillRect(ren, &node);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderDrawRect(ren, &node);

}

void	draw_links(t_node *current, SDL_Renderer *ren, int factor)
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
	t_node *ptr;

	ptr = head;
	while (ptr)
	{
		draw_links(head, ren, factor);
		ptr = ptr->next;
	}
	ptr = head;
	while (ptr)
	{
		draw_nodes(head, ren, factor);
		ptr = ptr->next;
	}

	SDL_RenderPresent(ren);
	SDL_Delay(5000);
}