/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:12 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 17:47:51 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
# define LEM_IN

# include "../libft/src/haflib.h"
# include "fcntl.h"

/*
**	Role : (0 = node; 1 = start; 2 = end)
*/
typedef struct		s_node
{
	struct s_node	*links;
	struct s_node	*next;
	char			*name;
	int				role;
}					t_node;


/*
**	PARSING FUNCTIONS
*/
t_node		*load_map(int argc, char ** argv, int *ant_nb);
t_node		*load_structure(char *data, int *ant_nb);
t_node		*add_node(t_node *head, char *line, int pos);
void		free_nodes(t_node *head);

#endif