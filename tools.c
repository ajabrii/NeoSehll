/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:51 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/09 15:20:41 by ytarhoua         ###   ########.fr       */
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