/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   haflib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conoel <conoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:03:06 by conoel            #+#    #+#             */
/*   Updated: 2019/02/14 08:33:32 by conoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AF_LIB_H
# define AF_LIB_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>

# define BUFF_SIZE 16m
# define ITER_MAX (INT_MAX / BUFF_SIZE)

int				ft_printf(const char *str, ...);

void				exit_free(char *msg, int format, ...);
void				free_tab(char **tab);
void				exit_(char *msg);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_strsplit(char *s, char c);
long long			ft_strtoll(char *ptr, size_t *index, int base);
int					ft_getc(int fd);
void				print_char_str(char c, size_t nb);
char				*get_the_file(int fd);
void				*ft_bzero(void *s, size_t n);
char				*ft_strdup(const char *s);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
void				print_int_str(int *tab, size_t len);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isalphanum_base(int c, int base, int maj);

#endif