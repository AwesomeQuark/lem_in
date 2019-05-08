/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 00:46:24 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/08 19:37:44 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*save_table(int *table)
{
	int		i;
	int		j;
	int		*prv_tbl;

	i = -1;
	prv_tbl = NULL;
	while (table[++i] != INT_MIN)
		;
	if (i > 1)
	{
		if (!(prv_tbl = (int*)malloc(sizeof(int) * (i + 1) * 2)))
			return (NULL);
		prv_tbl[i] = INT_MIN;
		j = i;
		i = -1;
		while (prv_tbl[++i] != INT_MIN)
		{
			prv_tbl[i] = table[j + 1 + i];
			prv_tbl[j + i + 1] = table[j + 1 + i];
		}
	}
	return (prv_tbl);
}

int		compare_tables(int *table, int *prv_tbl)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (table[++j] != INT_MIN)
		;
	if (prv_tbl)
	{
		while (prv_tbl[++i] != INT_MIN)
		{
			if (prv_tbl[j + i] != INT_MIN && prv_tbl[j + i] < table[j + 1 + i])
				return (1);
		}
	}
	return (0);
}
