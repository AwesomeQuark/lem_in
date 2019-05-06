/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:41:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/06 02:50:01 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	build_future2(t_node **room, t_path **vzt_nxt, t_path **reinit, int i)
{
	if ((*room)->links[i]->access == CLSD && (*room)->role != START)
		closed_access_case(room, vzt_nxt, i, reinit);
	else if (((*room)->links[i])->vzt == FREE
			&& ((*room)->links[i])->role != START
			&& (((*room)->flux[i] <= 0 && (*room)->links[i]->access == OPEN)))
	{
		if (!*vzt_nxt)
			*vzt_nxt = new_path((*room)->links[i]);
		else
			add_path((*room)->links[i], *vzt_nxt);
		*room = build_path(*room, i);
		((*room)->links[i])->vzt = VISITED;
	}
}

t_path	*build_future(t_node *room, t_path *vzt_nxt,
		t_node *head, t_path *reinit)
{
	int		i;

	i = -1;
	if (!room->flux)
		create_flux(&room);
	while (room->links[++i])
	{
		if (room->skip == 1)
		{
			room->skip = 0;
			room->vzt = 0;
			break ;
		}
		if (room->access == CLSD && room->links[i]->access == OPEN
				&& room->flux[i] <= 0)
		{
			if (skip_from_close(&room, i))
				;
		}
		build_future2(&room, &vzt_nxt, &reinit, i);
		if (flux_to_end(&room, &vzt_nxt, i, head) == 1)
			break ;
	}
	return (vzt_nxt);
}

int		test_function2(t_node *head, int ant_nb, int *loops, int **table)
{
	int		*prv_tbl;

	prv_tbl = NULL;
	if (*table)
	{
		prv_tbl = save_table(*table);
		free(*table);
	}
	*table = calc_paths(get_start(head), ant_nb);
	if (*table == NULL)
		return (1);
	*loops = *loops - 1;
	if (reset_or_not(*table, ant_nb, &head) == -1)
	{
		*loops = *loops + 1;
		return (1);
	}
	else if (compare_tables(*table, prv_tbl))
	{
		*loops = 0;
	   return (0);	
	}
	return (0);
}

int		*test_function(t_node *head, long ant_nb, int *loops)
{
	t_path	*vzt_nxt;
	t_node	*room;
	t_path	*reinit;
	int		*table;

	vzt_nxt = NULL;
	reinit = NULL;
	table = NULL;
	while (*loops > 0)
	{
		room = get_start(head);
		while (1)
		{
			vzt_nxt = build_future(room, vzt_nxt, head, reinit);
			if ((vzt_nxt && vzt_nxt->room->role == END) || !vzt_nxt)
				break ;
			reinit = visit_paths(&room, &vzt_nxt, reinit);
		}
		reinit_visited(&reinit);
		reinit_visited(&vzt_nxt);
		if (test_function2(head, ant_nb, loops, &table) == 1)
			break ;
	}
	return (table);
}
