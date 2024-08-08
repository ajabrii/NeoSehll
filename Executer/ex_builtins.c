/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:47:38 by kali              #+#    #+#             */
/*   Updated: 2024/08/08 12:23:46 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

bool is_builtin(t_node *root)
{
    if (!ft_strcmp(root->args,"cd"))
        return (true);
    if (!ft_strncmp(root->args,"env", 3))
        return (true);
    if (!ft_strncmp(root->args,"exit", 4))
        return (true);
    if (!ft_strncmp(root->args,"pwd", 3))
        return (true);
    if (!ft_strncmp(root->args,"unset", 5))
        return (true);
    if (!ft_strncmp(root->args,"echo", 4))
        return (true);
    if (!ft_strncmp(root->args,"export", 6))
        return (true);
    // if (!ft_strncmp(root->args,"./minishell", 11))
    //     return (true);
    else
        return (false);
}

int     ex_builtins(t_node *root)
{
    if (!ft_strcmp(root->args,"cd"))
    {
        bt_cd(root->args + 2);
        return (0);
    }
    if (!ft_strncmp(root->args,"env", 3))
        return (ft_env(neobash.envl), 0);
    if (!ft_strncmp(root->args,"exit", 4))
    {
        // printf("here [%s]\n", root->args);
        ft_exit(root->args + 4);
        return (0);
    }
    if (!ft_strncmp(root->args,"pwd", 3))
    {
        // printf("here [%s]\n", root->args);
        ft_pwd(root->args);
        return (0);
    }
    if (!ft_strncmp(root->args,"unset", 5))
        return (ft_unset(root->args + 5), 0);
    if (!ft_strncmp(root->args,"echo", 4))
        return (ft_echo(root->args + 4), 0);
    if (!ft_strncmp(root->args,"export", 6))
        return (ft_export(root->args + 6), 0);
    else
        return (1);
}
