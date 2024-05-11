/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:30:56 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/11 15:17:08 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef NEOSHELL_H
# define NEOSHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "utills/utils.h"

typedef enum e_token
{
	SP,
	RE, // >
	ER,	// <
	PIP, //PIPE
	APP, // APPEND >>
	PPA, // <<
	SQ, // ''
	DQ, // ""
	AND,
	CMD, //command
	OR
}          t_token;

typedef struct s_list
{
	char *env_var;
	struct s_list *next;
}			t_list;

typedef struct s_global
{
	int env_size;
	char	**envp;
	char 	*line;
	int		*arry;
	char	*linev2;
	
} 			t_data;

/* <tools.c> */
t_list	*ft_lstnew(char *var);
void	ft_lstadd_back(t_list **lst, t_list *newx);
t_list	*ft_lstlast(t_list *lst);
int		ft_strstr(const char *big, const char *little);
int		ft_strchr(const char *s, int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
/* </tools.c> */

/* <Neotoken.c> */
void	edit_line(t_data *data);
/* </Neotoken.c> */

#endif
