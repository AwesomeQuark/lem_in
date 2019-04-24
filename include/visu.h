/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:16:32 by conoel            #+#    #+#             */
/*   Updated: 2019/04/24 20:03:19 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "lem_in.h"
# include "haflib.h"
# include "/Users/conoel/.brew/include/SDL2/SDL.h"

# define SIZE 0.3

typedef struct		s_visu
{
	t_ant			*ants;
	t_node			*start;
	t_node			*end;
	int				ant;
	SDL_Window		*win;
	SDL_Renderer 	*ren;
}					t_visu;

t_ant	*allocate_ants(long ant_nb, t_node *end);
t_node	*next_path(t_node *current);
int		update_ants(t_ant *ants, t_node *start, t_node *end, long ant_nb);

void	draw(t_node *head, SDL_Renderer *ren);
void	draw_map(t_node *head, SDL_Renderer *ren);

#endif