/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:30:56 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/12 18:42:59 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef NEOSHELL_H
# define NEOSHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "utils/utils.h"

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


/* </tools.c> */
int ft_strchr(const char *s, int c);

/* <Neotoken.c> */
void	parseline(t_data *data);
/* </Neotoken.c> */

#endif
