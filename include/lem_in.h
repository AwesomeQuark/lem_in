/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:12 by conoel            #+#    #+#             */
/*   Updated: 2019/03/20 16:14:28 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
# define LEM_IN

# include "../haflib/src/haflib.h"
# include "fcntl.h"

/*
**	Role : (0 = node; 1 = start; 2 = end)
*/
typedef struct		s_node
{
	struct s_node	**links;
	struct s_node	*next;
	char			*name;
	int				role;
	int				access;
}					t_node;

/*
**	PARSING FUNCTIONS
*/
t_node		*load_map(int argc, char ** argv, int *ant_nb);
t_node		*load_structure(char *data, int *ant_nb);
t_node		*add_node(t_node *head, char *line, int pos);
void		free_nodes(t_node *head);
t_node		*get_node(char *name, size_t len, t_node *head);
int			alloc_links_list(t_node *node, t_node *link);
int			verify_data(char *data);

/*
** NODE MANIPULATION UTILS
*/
t_node			*get_start(t_node *head);
t_node			*get_end(t_node *head);
t_node			*get_node(char *name, size_t len, t_node *head);

#endif