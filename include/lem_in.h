/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:12 by conoel            #+#    #+#             */
/*   Updated: 2019/04/21 18:47:15 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN
# define LEM_IN

# include "haflib.h"
# include "fcntl.h"

# include <stdio.h> //will need to delete

# define START		1
# define END		2
# define OPEN		1 //access
# define CLSD		0 //access
# define VISITED	1 //vzt
# define FREE		0 //vzt

/*
**	Role : (0 = node; 1 = start; 2 = end)
*/
typedef struct		s_node
{
	struct s_node	**links;
	struct s_node	*next;
	struct s_path	*hist; //history of path
	char			*name;
	int				role;
	int				access;
	int				vzt; //visited or not
	int				*flux; //value of path
	int				weight;
	int				skip;

	int				printed;//only a test variable for printing

}					t_node;

typedef struct		s_path //path to room
{
	struct s_path	*prev;
	t_node			*room;
	struct s_path	*next;
}					t_path;

typedef struct		s_ant
{
	struct s_ant	*next;
	t_node			*room;
	int				nb;
}					t_ant;

/*
**	PARSING FUNCTIONS
*/
t_node		*load_map(int argc, char ** argv, long *ant_nb);
t_node		*load_structure(char *data, long *ant_nb);
t_node		*add_node(t_node *head, char *line, int pos);
void		free_nodes(t_node *head);
t_node		*get_node(char *name, size_t len, t_node *head);
int			alloc_links_list(t_node *node, t_node *link);
int			verify_data(char *data);
int			basic_solver(t_node *head);

/*
** NODE MANIPULATION UTILS
*/
t_node			*get_start(t_node *head);
t_node			*get_end(t_node *head);
t_node			*get_node(char *name, size_t len, t_node *head);
t_node			*get_next_open_link(t_node *node);
void			reset_nodes(t_node *head);
/*
** PATH MANIPULATION UTILS
*/

void	closed_access_case(t_node **room, t_path **vzt_nxt, int idx,
		t_path **reinit);

/*
** PATH MANIPULATION UTILS
*/
t_path	*new_path(t_node *node);
int		add_path(t_node *node, t_path *path);
void	remove_path(t_path *path);
int		solver(t_node *head);

t_path	*copy_path(t_path *path);

t_path	*new_path(t_node *node);
int		add_path(t_node *node, t_path *path);
t_path	*deprecate_first(t_path **path, t_path *deprecated);
void	reinit_visited(t_path **history);
int		compare_weights(t_node **room, int idx);
int		skip_from_close(t_node **room, int idx);
int		check_outwardflux(t_node **room);

/*
** FLUX MANIPULATION UTILS
*/

int		find_index(t_node *prev, t_node *next);//find correct index to next node room
int		reverse_flux_case(t_node *room, int idx);
void	adjust_reverse_flux(t_node **room, int idx);
void	create_flux(t_node **room);


/*
** PATH PHASE
*/
void		test_function(t_node *head);
void		shortest_path(t_node **room, int size, t_node *head);
t_node		*build_paths(t_node *room);

t_node		*build_path(t_node *room, int i);

void		print_nodes(t_node *head);
void		print_path_test(t_path *head);
void		print_path_final(t_path *head);
void		print_flux(t_node *room);

void		test_flux(t_node *room);

/*
**	LAST DISPLAY
*/

int		display_end(t_node *head, long ant_nb, char *opt);

/*
** TESTNG PHASE
*/

int		count_edges(t_node *room);
int		count_iterations(t_node *head);


#endif
