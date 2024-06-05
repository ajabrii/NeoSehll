/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:51 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/06/05 09:23:28 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HEADERS/neoshell.h"
#include 	"../HEADERS/utils.h"

void	ft_lstadd_backv2(t_leak **lst, t_leak *newx)
{
	t_leak	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlastv2(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size + 1);
	if(!res)
		return (NULL);
	ft_lstadd_backv2(&shell.leaks, ft_lstnewv2(res));
	// hear when ever i use this malloc i well create an node
	//  that hold the address and free this linked list
	// the goal is to have the 0 leaks
	return (res);
}

t_leak	*ft_lstnewv2(void *var)
{
	t_leak	*lst;

	lst = (t_leak *)malloc(sizeof(t_leak));
	if (!lst)
		return (NULL);
	lst->address = var;
	lst->next = NULL;
	return (lst);
}

t_leak	*ft_lstlastv2(t_leak *lst)
{
	t_leak	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void ft_lstadd_back(t_envl **lst, t_envl *newx)
{
	t_envl	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlast(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}


size_t ft_strlenc(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}


t_envl	*ft_lstnew(char *var)
{
	t_envl	*lst;
	int		len;

	lst = (t_envl *)malloc(sizeof(t_envl));
	if (!lst)
		return (NULL);
	lst->envar = ft_malloc(ft_strlenc(var, '='));
	ft_strcpy(lst->envar, var, '=');
	len = ft_strlen(lst->envar);
	lst->value = ft_malloc(ft_strlenc((var + len), '\0'));
	ft_strcpy(lst->value, var + len + 1, '\0');
	lst->next = NULL;
	return (lst);
}


t_envl	*ft_lstlast(t_envl *lst)
{
	t_envl	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}


int	ft_strchr(const char *s, int c)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (s[z])
		z++;
	while (i <= z)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_lstsize(t_envl *lst)
{
	int		len;
	t_envl	*tmp;

	tmp = lst;
	len = 0;
	if (lst == NULL)
		return (0);
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}