/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_remaining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:25:35 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/01 15:46:03 by bghandou         ###   ########.fr       */
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
