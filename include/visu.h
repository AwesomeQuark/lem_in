/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:16:32 by conoel            #+#    #+#             */
/*   Updated: 2019/05/03 10:39:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "lem_in.h"
# include "haflib.h"
# include "/Users/conoel/.brew/include/SDL2/SDL.h"
// include "SDL2/SDL.h"

# define SIZE 30

typedef struct		s_visu
{
	t_ant			*ants;
	t_node			*start;
	t_node			*end;
	int				ant;
	SDL_Window		*win;
	SDL_Renderer 	*ren;
}					t_visu;

int		sdl_start(SDL_Window **win, SDL_Renderer **ren);
void	sdl_end(SDL_Window *win, SDL_Renderer *ren);
void	draw(t_node *head, SDL_Renderer *ren, int factor);
void	draw_map(t_node *head, SDL_Renderer *ren, int factor);

#endif
