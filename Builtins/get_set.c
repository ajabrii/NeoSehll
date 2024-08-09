/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:05:43 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:55 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*get_env_val(char *key)
{
	t_env	*envlst;

	envlst = neobash.envl;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	update_env(char *key, char *value)
{
	t_env	*envlst;

	envlst = neobash.envl;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = ft_strdup(value);
			return ;
		}
		envlst = envlst->next;
	}
	// free(value);
}

t_env	*exp_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!value)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	exp_back(t_env *new)
{
	t_env	*curr;

	if (!neobash.envl)
	{
		neobash.envl = new;
		return ;
	}
	curr = neobash.envl;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}
