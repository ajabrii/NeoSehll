/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:51 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/11 14:23:57 by ytarhoua         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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