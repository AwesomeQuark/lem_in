/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_remaining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:25:35 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 19:21:18 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	fill_remaining(int *table, long ant_nb)
{
	int		i;
	int		sum;
	int		rem;

	i = -1;
	sum = 0;
	rem = 0;
	if (table == NULL)
		return ;
	while (table[++i])
		sum += table[i];
	if (sum == (int)ant_nb)
		return ;
	else
	{
		i = 0;
		rem = (int)ant_nb - sum;
		while (rem > 0 && table[i])
		{
			table[i] = table[i] + 1;
			i++;
			rem--;
		}
	}
}

void	check_startend(int *table, long ant_nb, t_node *start)
{
	int		i;
	int		j;
	int		flag;
	
	i = -1;
	j = 0;
	flag = 0;
	while (start->links[++i])
	{
		if (start->links[i]->role == END)
			flag = 1;
	}
	i = -1;
	while (start->links[++i] && flag == 1 && table)
	{
		if (start->links[i]->role == END)
			table[j++] = ant_nb;
		else if (start->flux[i] == 1)
		{
			table[j] = 0;
			j++;
		}
	}
}
