/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:30:56 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/14 21:29:33 by ajabri           ###   ########.fr       */
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
	WR,
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

	// draft
	char *tmp;
	char *palestine;

} 			t_data;

typedef struct s_type
{
	t_token type;
	char *value;
	struct s_type *next;
}	t_type;

/* <tools.c> */
t_list	*ft_lstnew(char *var);
void	ft_lstadd_back(t_list **lst, t_list *newx);
void	ft_lstadd_backv2(t_type **lst, t_type *newx);
t_list	*ft_lstlast(t_list *lst);
t_type	*ft_lstlastv2(t_type *lst);
int	ft_lstsize(t_list *lst);



/* </tools.c> */
int ft_strchr(const char *s, int c);

/* <Neotoken.c> */
void	parseline(t_data *data);
int		ft_search(char *str);
/* </Neotoken.c> */

char 	**grep_paths(char **env);
char *get_cmd_path(t_data *pp, char **paths, char *cmd);
void ft_exit(int exx);

#endif
