/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:41:17 by conoel            #+#    #+#             */
/*   Updated: 2019/03/18 19:38:05 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static t_node	*load_nodes(char *data, size_t *i)
{
	t_node	*head;
	size_t	j;
	int		pos;

	while (data[*i])
	{
		j = 0;
		while (data[*i + j] != '\n' && data[*i + j])
			j++;
		if (ft_memchr(&data[*i], ' ', j) == NULL && data[*i] != '#')
			break;
		(ft_memcmp(&data[*i], "##start\n", 8) == 0) ? pos = 1 : 0;
		(ft_memcmp(&data[*i], "##end\n", 6) == 0) ? pos = 2 : 0;
		if (data[*i] != '#')
		{
			if (!(head = add_node(head, &data[*i], pos)))
				return (NULL);
			pos = 0;
		}
		*i = *i + j + 1;
	}
	return (head);
}

static int		load_links(t_node *head, char *data)
{
	t_node	*ptr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i + j] != '\n' && data[i + j])
			j++;
		if (ft_memchr(&data[i], '-', j) == NULL && data[i] != '#')
			return(return_("Bad character in the links list\n"));
		if (data[i] != '#')
		{
			k = 0;
			while (data[i + k] != '-' && data[i + k])
				k++;
			ptr = get_node(&(data[i + k + 1]), j - (k + 1), head);
			if (!(alloc_links_list(get_node(&(data[i]), k, head), ptr)))
				return (0);
			if (!(alloc_links_list(ptr, get_node(&(data[i]), k, head))))
				return (0);
		}
		i = i + j + 1;
	}
	return (1);
}

t_node			*load_structure(char *data, int *ant_nb)
{
	size_t	i;
	t_node	*head;

	i = 0;
	*ant_nb = ft_strtoll(data, &i, 10);
	i++;
	if (!(head = load_nodes(data, &i)))
		return (NULL);
	//if (!(load_links(head, &data[i])))
	//	return (NULL);
	return (head);
}