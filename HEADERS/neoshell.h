/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:11:53 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/05 15:49:04 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef NEOSHELL_H
# define NEOSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
# include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT G "🌟::NeoShell~/💎[" ORG "Prompt" RES G "]🗿$\n|~↠$ " RES

/*lexical*/
typedef enum s_token
{
    WR,
    OPTION,
    REDIRECTION,
    INPUT,
    PIPE,
    WSP, //white spaces
    HERE_DOC,
    APPEND,
    AND,
    OR,
    L_PAR, // (
    R_PAR,// )
    STAR,
}          t_token;

/*THE LEAXICAL LINKED LIST*/
typedef struct s_lexical
{
    char *value;
    t_token token;
    struct s_lexical *next;
}   t_block;

/*envp linked list*/
typedef struct s_env
{
    char *envar;// envp variable name
    char *value; //the value of the var
    struct s_env *next;
}               t_envl; //env_list

/*this linked list helps me to free all memory address*/
typedef  struct s_leak
{
    void            *address;
    struct s_leak   *next;
}               t_leak;

/*the global struct*/
typedef struct s_neo
{
    char    **envp;
    char    *line;
    t_envl  *envl;
    t_leak  *leaks;
    t_block *block;
    char    **sub;// this for tokenization
    size_t size;
} g_neo;

extern g_neo shell;

t_envl *ft_lstlast(t_envl *lst);
t_envl *ft_lstnew(char *var);
void    ft_lstadd_back(t_envl **lst, t_envl *newx);
void    ft_strcpy(char *dst, char *src, char c);
void    ft_env(t_envl *env);
void    ft_exit(int x);

t_leak *ft_lstlastv2(t_leak *lst);
t_leak *ft_lstnewv2(void *var);
void ft_lstadd_backv2(t_leak **lst, t_leak *newx);
void ft_free_leaks();

void give_token();
void ft_lexical();
void *ft_malloc(size_t size);
void ft_throwerr(char *err, int flag);
#endif