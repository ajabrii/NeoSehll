/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/01 20:45:38 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HEADERS/neoshell.h"
# include "../HEADERS/utils.h"

t_envl *search_env(char *s)
{
    g_neo *data;
    t_envl *env = data->envl;
    t_envl *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->envar, ft_strlen(s)))
            return (tmp->value);
        tmp->next;
    }
    tmp = env;
    return (NULL);
}

void ft_pwd(char *s)
{
    g_neo *data;
    t_envl *value = search_env(s);
    if (value)
        printf("%s\n", value);
}
