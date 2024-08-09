/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:47:38 by kali              #+#    #+#             */
/*   Updated: 2024/08/09 12:05:26 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

bool is_builtin()
{
    if (!ft_strcmp(neobash.argss[0],"cd"))
        return (true);
    if (!ft_strcmp(neobash.argss[0],"env"))
        return (true);
    if (!ft_strcmp(neobash.argss[0],"exit"))
        return (true);
    if (!ft_strcmp(neobash.argss[0],"pwd"))
        return (true);
    if (!ft_strcmp(neobash.argss[0],"unset"))
        return (true);
    if (!ft_strcmp(neobash.argss[0],"echo"))
        return (true);
    if (!ft_strcmp(neobash.argss[0],"export"))
        return (true);
    // if (!ft_strncmp(root->args,"./minishell", 11))
    //     return (true);
    else
        return (false);
}

int     ex_builtins(t_node *root)
{
    if (!ft_strcmp(neobash.argss[0],"cd"))
        return (bt_cd(neobash.argss));
    if (!ft_strcmp(neobash.argss[0],"env"))
        return (ft_env(neobash.envl), 0);
    if (!ft_strcmp(neobash.argss[0],"exit"))
    {
        // printf("here [%s]\n", root->args);
        ft_exit(neobash.argss);
        return (0);
    }
    if (!ft_strcmp(neobash.argss[0],"pwd"))
    {
        // printf("here [%s]\n", root->args);
        ft_pwd(neobash.argss);
        return (0);
    }
    if (!ft_strcmp(neobash.argss[0],"unset"))
        return (ft_unset(neobash.argss), 0);
    if (!ft_strcmp(neobash.argss[0],"echo"))
        return (ft_echo(root->args + 4), 0);
    if (!ft_strcmp(neobash.argss[0],"export"))
        return (ft_export(root->args + 6), 0);
    else
        return (1);
}
