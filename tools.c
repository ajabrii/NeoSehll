/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:51 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/21 20:11:19 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neoshell.h"

void	ft_lstadd_back(t_list **lst, t_list *newx)
{
	t_list	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlast(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

void	ft_lstadd_backv2(t_type **lst, t_type *newx)
{
	t_type	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlastv2(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

t_list	*ft_lstnew(char *var)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->env_var = ft_strdup(var);
	lst->next = NULL;
	return (lst);
}

t_type	*ft_lstnewv2(char *var, t_token token, bool flag)
{
	t_type	*lst;

	lst = (t_type *)malloc(sizeof(t_type));
	if (!lst)
		return (NULL);
	lst->value = ft_strdup(var);
	lst->type = token;
	lst->flag = flag;
	lst->next = NULL;
	return (lst);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_type	*ft_lstlastv2(t_type *lst)
{
	t_type	*tmp;

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

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*tmp;

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