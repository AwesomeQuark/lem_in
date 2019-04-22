/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:12:09 by conoel            #+#    #+#             */
/*   Updated: 2019/04/22 18:38:37 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	display_nodes(t_token *head)
{
	while (head)
	{
		printf("<%s [%d]> ", head->content, head->type);
		head = head->next;
	}
}

int		main(int argc, char **argv)
{
	t_token		*head;
	SDL_Window	*win;
	SDL_Renderer *ren;

	if (argc != 2)
	{
		ft_printf("Usage : ./visu [file_name]\n");
		return (0);
	}
	if (!(head = lexer(open(argv[1], O_RDONLY))))
		return (0);
	if (!(sdl_start(&win, &ren)))
		return (0);
	display_nodes(head);
	sdl_end(win, ren);
	return (1);
}