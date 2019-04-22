/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:52:03 by conoel            #+#    #+#             */
/*   Updated: 2019/04/22 18:49:20 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_def	tokens[] =
{
	{"##start", 7, START_COMM},
	{"##end", 5, END_COMM},
	{"#", 1, COMM},
	{"L", 1, ANT},
	{NULL, 0, STOP}
};

static int		handle_escape(char **file)
{
	if (*file[0] == '\n')
		return (1);
	if (*file[0] == '#' && *file[1] != '#')
	{
		while (*file && *file[0] != '\n')
		{
			(*file) += 1;
			printf("h%p\n", *file);
		}
	}
	return (0);
}

static t_token_def	*search_token_type(char *file)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != STOP)
	{
		if (ft_strncmp(file, tokens[i].content, tokens[i].size) == 0)
			return (&tokens[i]);
		i++;
	}
	return (NULL);
}

int				lexer_main_loop(char *file, t_token *head)
{
	t_token_def	*current;
	char		*last_token_found;

	last_token_found = file;
	while (file && *file)
	{
		if (handle_escape(&file))
		{
			if (last_token_found != file && head->next != NULL)
				add_token(last_token_found, file - last_token_found, misc_type(last_token_found, file - last_token_found), head);
			file++;
			last_token_found = file;
			continue ;
		}
		if (!(current = search_token_type(file)))
		{
			file++;
			continue ;
		}
		if (last_token_found != file && head->next != NULL)
			add_token(last_token_found, file - last_token_found, misc_type(last_token_found, file - last_token_found), head);
		file += current->size;
		last_token_found = file;
		if (!(add_token(current->content, current->size, current->type, head)))
			return (0);
	}
	if (last_token_found != file && head->next != NULL)
		add_token(last_token_found, file - last_token_found, misc_type(last_token_found, file - last_token_found), head);
	return (1);
}

t_token			*lexer(int fd)
{
	t_token	*head;
	char	*file;
	size_t	i;

	if (fd < 0)
		return (NULL);
	i = 0;
	if (!(file = get_the_file(fd)))
		return (NULL);
	printf("%s\n", file);
	if (!(head = malloc(sizeof(t_token))))
	{
		free(file);
		return (NULL);
	}
	head->type = START;
	head->next = NULL;
	head->size = 0;
	head->content = NULL;
	if (!(lexer_main_loop(file, head)))
	{
		free(file);
		return (0);
	}
	free(file);
	return (head);
}