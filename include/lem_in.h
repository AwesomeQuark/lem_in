/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:12 by conoel            #+#    #+#             */
/*   Updated: 2019/03/16 18:57:46 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
# define LEM_IN

# include "haflib.h"

typedef struct	s_edge
{
	t_node	*links;
	int		id;
	int		x;
	int		y;
}				t_edge;

typedef struct	s_node
{
	int		id1;
	int		id2;
}				t_node;

#endif