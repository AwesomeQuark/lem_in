/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:50:26 by conoel            #+#    #+#             */
/*   Updated: 2019/03/21 13:40:19 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static int	error(int line, int type, char c)
{
	if (type == 1)
		ft_printf("Error in the ants number\n");
	else if (type == 2)
		ft_printf("Error line %d [char: %c]\n", line, c);
	else 
		ft_printf("wrong terminating character line %d\n", line);
	return (0);
}

static int	verify_line(char *data, size_t *i, int line)
{
	while (data[*i] != ' ') // passer le nom de la salle
	{
		if (data[*i] == '-')  // c'est un lien ! On quitte, le reste du programme s'en occupe ;P
			return (2);
		*i += 1;
	}
	ft_strtoll(&data[*i], i, 10);   // passer coordonnee 1
	if (data[(*i)++] != ' ')         // verifier l'espace
		return (error(line, 2, data[(*i) - 1]));
	ft_strtoll(&data[*i], i, 10); //passer coordonnee 2
	return (1);
}

int			verify_data(char *data)
{
	size_t	i;
	int		line;
	int		ret;

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
		else // si c'est une ligne normale
		{
			ret = verify_line(data, &i, line);
			if (ret == 2) //c'est un lien, on passe la main au reste du programme
				return (1);
			if (ret == 0) //mauvaise ligne on quitte :()
				return (0);
		}
		if (data[i++] != '\n') //verifie le dernier charactere de la ligne
			return (error(line, 3, data[i - 1]));
		line++;
	}
	return (1);
}
