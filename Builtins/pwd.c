/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/03 18:44:21 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

t_env *search_env(char *s)
{
    g_shell *data;
    t_env *env = data->envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
            return (tmp->value);
        tmp->next;
    }
    tmp = env;
    return (NULL);
}

void ft_pwd(char *s)
{
    t_env *v = search_env(s);
    if (v == NULL)
    {
        printf("bash: pwd: '%s': invalid option", s);
        return;
    }
    if (v->value)
        ft_putstr_fd(v->value, 1);
	ft_putstr_fd("\n", 1);
}

