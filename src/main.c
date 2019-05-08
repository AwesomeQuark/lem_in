/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:53:06 by conoel            #+#    #+#             */
/*   Updated: 2019/05/08 16:28:50 by conoel           ###   ########.fr       */
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

int			main(int argc, char **argv)
{
	t_node	*head;
	long	ant_nb;
	int		loops;
	int		diff;
	int		*table;

	if (!(head = load_map(argc, argv, &ant_nb)))
		return ((int)return_("Failed to load the map"));
	loops = count_iterations(head);
	diff = loops;
	table = test_function(head, ant_nb, &loops);
	diff -= loops;
	if (loops > 0)
	{
		free(table);
		reinit_all(head);
		table = test_function(head, ant_nb, &diff);
	}
	fill_remaining(table, ant_nb);
	check_startend(table, ant_nb, get_start(head));

	int i = -1;
	int	j = 0;
	int	path = 0;
	int	max = 0;
	t_node *start = get_start(head);
//	print_nodes(head);
	while (start->links[++i])
	{
		if (start->flux[i] == 1)
		{
			dprintf(1, "------------\n");
			ft_printf("room %s to %s %d\n", start->name, start->links[i]->name, i);
			path = test_flux(start->links[i]);
			dprintf(1, "ants to send = %d || path len %d || total cycles : %d\n", table[j], path, path + table[j] - 1);
			dprintf(1, "------------\n");
			if (path + table[j] - 1 > max)
				max = path + table[j] - 1;
			j++;
		}
	}
	printf("EXPECTED |%d\n\n", max);
	if (argc == 3 && ft_strncmp(argv[2], "-v", 2) == 0)
		display_end_visu(head, ant_nb, ft_atoi(&argv[2][2]), table);
	else
		display_end(head, ant_nb, table);
	free_nodes(head);
	free(table);
}
