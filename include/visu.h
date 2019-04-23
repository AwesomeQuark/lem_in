/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:16:32 by conoel            #+#    #+#             */
/*   Updated: 2019/04/23 15:23:59 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "haflib.h"
# include "/Users/conoel/.brew/include/SDL2/SDL.h"

int		sdl_start(SDL_Window **win, SDL_Renderer **ren);
void	sdl_end(SDL_Window *win, SDL_Renderer *ren);


#endif