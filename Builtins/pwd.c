/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 12:07:43 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

t_env *search_envl(char *s)
{
    t_env *env = neobash.envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
            return (tmp);
        tmp = tmp->next;
    }
    tmp = env;
    return (NULL);
}

//to check option like pwd -h -> error

int option(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (1);
    while (str[i])
    {
        if (str[i] == '-')
        {
            printf("bash: pwd: '%s': invalid option\n", &str[i]);
            neobash.status = 2;
            return (1);
        }
        i++;
    }
    // if (i > 3)
    //     return (1);
    return (0);
}

void ft_pwd(char **s)
{
    int c;
    char *path;

    c = 1;
    if (option(s[c]))
        return;
    path = get_env_val("PWD");
    // printf ("str is ::%s\n", s);
    // printf("v->value is ::%s\n", path);
    if (path)
        ft_putstr_fd(path, 1);
    if (path == NULL)
    {
	    path = getcwd(path, 0);
	    if (!path)
        {
            free(path);
            return;
        }
	    ft_putstr_fd(path, 1);
    }
    free(path);
	ft_putstr_fd("\n", 1);
}
