/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:16:32 by conoel            #+#    #+#             */
/*   Updated: 2019/05/04 12:28:06 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "lem_in.h"
# include "haflib.h"
# include "/Users/conoel/.brew/include/SDL2/SDL.h"
// include "SDL2/SDL.h"

# define SIZE 30
# define STEP 100
# define TIME_MOV 1000

typedef struct		s_visu
{
	t_ant			*ants;
	t_node			*start;
	t_node			*end;
	int				ant;
	int				size;
	SDL_Window		*win;
	SDL_Renderer 	*ren;
}					t_visu;

int sdl_start(t_visu *var, int width, int height);
void sdl_end(SDL_Window *win, SDL_Renderer *ren);
int height_map(t_node *head);
int	width_map(t_node *head);
void draw(t_node *head, t_visu *var, int *table);
t_node	*next_path(t_node *current);
t_ant	*allocate_ants(long ant_nb, t_node *end);
int	remaining_space(int *table, t_node *start, int mode);
int		update_ants(t_ant *ants, t_node *head, int *table);

#endif
