/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:50:26 by conoel            #+#    #+#             */
/*   Updated: 2019/03/20 14:58:29 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static int	error(int line, int type, char c)
{
	ft_printf("Error line %d [char: %c] [type: %d]\n", line, c, type);
	return (0);
}

static int	verify_line(char *data, int *i, int line)
{
	while (data[*i] != ' ') // passer le nom de la salle
	{
		if (data[*i] == '-')  // c'est un lien ! On quitte, le reste du programme s'en occupe ;P
			return (1);
		*i += 1;
	}
	ft_strtoll(&data[*i], &i, 10);   // passer coordonnee 1
	if (data[(*i)++] != ' ')         // verifier l'espace
		return (error(line, 2, data[*i]));
	ft_strtoll(&data[*i], &i, 10); //passer coordonnee 2
	return (0);
}

int			verify_data(char *data)
{
	size_t	i;
	int		line;

	i = 0;
	line = 2;
	ft_strtoll(&data[i], &i, 10); //passer nombre de fourmis
	if (data[i++] != '\n')  //verifier fin de ligne
		return (error(line, 1, data[i]));
	while (data[i])
	{
		if (data[i] == '#') // si c'est un commentaire
			while (data[i] != '\n')
				i++;
		else
			if (verify_line(data, &i, line)) //si c'est une ligne
				return (1);
		if (data[i++] != '\n')
			return (error(line, 3, data[i]));
		line++;
	}
	return (1);
}
