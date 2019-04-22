/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:16:32 by conoel            #+#    #+#             */
/*   Updated: 2019/04/22 18:31:31 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <fcntl.h>
# include "haflib.h"
# include "/Users/conoel/.brew/include/SDL2/SDL.h"
# include "lexer.h"


typedef	struct s_node
{
	struct s_node 	*next;
	char 			*name;
	int				x;
	int				y;
	int				role;
}				t_node;

# define END 1
# define START 2

int		sdl_start(SDL_Window **win, SDL_Renderer **ren);
void	sdl_end(SDL_Window *win, SDL_Renderer *ren);


#endif