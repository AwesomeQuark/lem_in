/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:16:32 by conoel            #+#    #+#             */
/*   Updated: 2019/04/27 15:26:16 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "lem_in.h"
# include "haflib.h"
# include "/Users/conoel/.brew/include/SDL2/SDL.h"

# define SIZE 25
# define MAX_W 2560
# define MAX_H 1440
# define STEP 100
# define TIME_MOV 1000

typedef struct		s_ant
{
	struct s_ant	*next;
	t_node			*room;
	int				nb;
}					t_ant;

typedef struct		s_visu
{
	t_ant			*ants;
	t_node			*start;
	t_node			*end;
	int				ant;
	SDL_Window		*win;
	SDL_Renderer 	*ren;
	int				size;
}					t_visu;

int		width_map(t_node *head);
int		height_map(t_node *head);
int		sdl_start(t_visu *var, int width, int height);
void	sdl_end(SDL_Window *win, SDL_Renderer *renderer);

t_ant	*allocate_ants(long ant_nb, t_node *end);
t_node	*next_path(t_node *current);
int		update_ants_visu(t_ant *ants, t_node *start, t_node *end, long ant_nb);

void	draw(t_node *head, t_visu *var);

#endif