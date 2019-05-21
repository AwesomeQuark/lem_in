/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:06 by conoel            #+#    #+#             */
/*   Updated: 2019/05/21 15:54:25 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_links(t_node *node)
{
	int	i;

	i = 0;
	if (node->links == NULL)
		return ;
	while ((node->links)[i] != NULL)
	{
		ft_printf("%8s ", ((node->links)[i])->name);
		i++;
	}
}

void		print_nodes(t_node *head)
{
	while (head != NULL)
	{
		ft_printf("NAME : %8s ROLE : %d LINKED TO : ",
			head->name, head->role, head->next);
		print_links(head);
		ft_printf("\n");
		head = head->next;
	}
}

void		do_bfs(t_node *head, int **table, long ant_nb)
{
	int		loops;
	int		diff;

	loops = count_iterations(head);
	diff = loops;
	*table = test_function(head, ant_nb, &loops);
	diff -= loops;
	if (loops > 0)
	{
		free(*table);
		reinit_all(head);
		*table = test_function(head, ant_nb, &diff);
	}
	fill_remaining(*table, ant_nb);
	check_startend(*table, ant_nb, get_start(head));
}

int			get_options(int argc, char **argv)
{
	size_t		i;
	int			params;

	i = 1;
	params = 0;
	if (argc != 3 || argv[1][0] != '-')
		return (32);
	while (argv[1][i])
	{
		if (argv[1][i] == 'v')
			params = params | VISU;
		else if (argv[1][i] == 'c')
			params = params | COUNT;
		else if (argv[1][i] == 'a')
			params = params | COLOR;
		else if (argv[1][i] == 's')
			params = params | SILENT;
		else
			return (return_("Usage: ./lem-in [-vcsa] [map.lem | < map.lem]\n"));
		i++;
	}
	return (params);
}

int			main(int argc, char **argv)
{
	t_node	*head;
	int		*table;
	long	ant_nb;
	int		params;

	if (!(params = get_options(argc, argv)))
		return (0);
	if (!(head = load_map(argc, argv, &ant_nb, params)))
		return ((int)return_("Failed to load the map"));
	do_bfs(head, &table, ant_nb);
	if (params & VISU)
		display_end_visu(head, ant_nb, table, params);
	else
		display_end(head, ant_nb, table, params);
	free_nodes(head);
	free(table);
}
