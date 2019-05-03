/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_equation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:22:10 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/03 15:04:25 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_length(t_node *start)
{
	int		i;
	int		path_len;

	i = -1;
	path_len = 0;
	while (start->links[++i])
	{
		if (start->flux)
		{
			if (start->flux[i] == 1 && start->links[i]->tag <= 0)
			{
				if (start->links[i]->role == 0)
					start->links[i]->tag = 1;
				start = start->links[i];
				i = -1;
				path_len++;
			}
		}
	}
	return (path_len);
}

int		*solve_equation(int n_paths, int *table, long ant_nb, int total_len)
{
	int		send_ants;
	int		i;

	send_ants = 0;
	i = -1;
	if (n_paths > 1)
	{
		while (table[++i] != INT_MIN)
		{
			table[i] = (ant_nb - (((n_paths - 1) * table[i])
						- (total_len - table[i]))) / n_paths;
			if (table[i] < 0)
				return (table);
		}
		return (table);
	}
	else
	{
		table[0] = ant_nb;
		return (table);
	}
	return (table);
}

int		*calc_paths(t_node *start, int ant_nb)
{
	int		i;
	int		n_paths;
	int		path_len;
	int		total_len;
	int		*table;

	i = -1;
	n_paths = 0;
	path_len = 0;
	total_len = 0;
	if ((n_paths = count_paths(start)) == 0)
			return (NULL);
	if (!(table = (int*)malloc(sizeof(int) * (n_paths + 1))))
		return NULL;
	table[n_paths] = INT_MIN;
	while (start->links[++i] && i < n_paths)
	{
		path_len = path_length(start);
	//	if (n_paths == 1 && path_len >= ant_nb) //had just return (NULL);
	//		return (NULL);
		total_len += path_len;
		table[i] = path_len;
	}
	table = solve_equation(n_paths, table, ant_nb, total_len);
	return (table);
}

int		check_viability(int *table, int ant_nb, t_node *head)
{
	int		i;
	int		loops;

	i = -1;
	loops = count_iterations(head);
	while (table[++i] != INT_MIN && loops > 0)
	{
		if (table[i] == ant_nb)
			return (0);
		else if (table[i] < 0)
			return (-1);
		loops--;
	}
	if (loops == 0)
		return (0);
	return (i);
}

int		reset_or_not(int *table, int ant_nb, t_node **head)
{
	int		i;
	t_node	*start;

	i = -1;
	start = get_start(*head);
	while (start->links[++i])
		flux_or_tag(get_start(start), 0);
	i = -1;
	if (check_viability(table, ant_nb, *head) == -1)
	{
		while (start->links[++i])
			flux_or_tag(get_start(start), -1);
		return (-1);
	}
	else if (check_viability(table, ant_nb, *head) == 0)
		return (0);
	else
		return (1);
	return (1);
}
