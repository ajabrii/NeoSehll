/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:39:54 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/05 08:56:02 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HEADERS/neoshell.h"
# include "../HEADERS/utils.h"

// g_neo shell;

void    ft_env(t_envl *env)
{
    t_envl *tmp;

    tmp = env;
    while (env)
    {
        printf("%s=%s\n",env->envar, env->value);
        env = env->next;
    }
    env = tmp;
}
