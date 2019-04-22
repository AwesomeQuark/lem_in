/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:14:29 by conoel            #+#    #+#             */
/*   Updated: 2019/04/22 18:41:41 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../haflib/includes/haflib.h"

typedef enum
{
	START,
	START_COMM,
	END_COMM,
	COMM,
	NODE,
	LINK,
	ANT,
	MISC_STRING,
	MISC_INT,
	STOP
} t_token_type;

typedef struct s_token_def
{
	char*			content;
	size_t			size;
	t_token_type	type;
}				t_token_def;

typedef struct s_token
{
	struct s_token	*next;
	char*			content;
	size_t			size;
	t_token_type	type;
}				t_token;

t_token			*lexer(int fd);
int				add_token(char *content, size_t size, t_token_type type, t_token *head);
t_token_type	misc_type(char *str, size_t size);

#endif