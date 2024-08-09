/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/09 12:03:45 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_before_exec(t_node *root)
{
    t_root_t tp;

    if (!root)
        return;
    tp = root->type;
    if (tp == PIPE_N || tp == OR_N || tp == AND_N)
    {
        ft_before_exec(root->left);
        // if (neobash.hdoc)
        ft_before_exec(root->right);
    }
    else
        ft_init_io(root);
}

void	ft_reset_stds()
{
	// if (piped)
	// 	return ;
	// printf("{%d}\n",neobash.in);
	dup2(neobash.in, 0);
	dup2(neobash.out, 1);
    dup2(neobash.err, 2);
}

unsigned int ex_cmd(t_node *root)
{
    // char **args;
    char *cmdpath;
    char **my_envp;
    pid_t pid;
    int ex;

    if (root->args)
    {
        neobash.argss = get_cmdagrs(root->args);
        if (is_builtin(root))
        {
            ex = ft_io(root, 0);
            if (ex)
            {
                ft_reset_stds();
                return (ex);
            }
            ex = ex_builtins(root);
            ft_reset_stds();
            return ex;
        }
        else
        {
            cmdpath = get_cmd_path(neobash.paths, neobash.argss[0]);
            if (!ft_strncmp(neobash.argss[0], "./minishell", 12))
            {
                printf(RED "`%s'\n" RES, neobash.argss[0]);
                update_env("SHLVL", ft_itoa(++neobash.level));
                printf("[%s]\n", get_env_val("SHLVL"));
            }
            pid = fork();
            if (pid == 0)
            {
                ex = ft_io(root, 0);
                if (ex)
                {
                    ft_reset_stds();
                    // ft_free_all();
                    exit(ex);
                }
                if (!cmdpath)
                {
                    ft_error("neobash: command not found: $", neobash.argss[0]);
                    ft_free_all();
                    exit(127);
                }
                else
                {
                    my_envp = get_my_envp();
                    execve(cmdpath, neobash.argss, my_envp);
                    perror("execve");
                    ft_free_all();
                    exit(1);
                }
            }
            else if (pid > 0)
            {
                waitpid(pid, &ex, 0);
                if (WIFEXITED(ex))
                {
                    ex = WEXITSTATUS(ex);
                }
                else if (WIFSIGNALED(ex))
                {
                    ex = 128 + WTERMSIG(ex);
                }
                ft_reset_stds();
                return ex;
            }
            else
            {
                perror("fork");
                return 1;
            }
        }
    }
    else
    {
        ex = ft_io(root, 1);
        if (ex)
        {
            return ex;
        }
    }
    return 0;
}


int ft_executer(t_node *root)
{
    int exit_status = 0;

    if (root->type == PIPE_N)
    {
        exit_status = ex_pipes(root);
    }
    else if (root->type == AND_N)
    {
        exit_status = ft_executer(root->left);
        if (exit_status == 0 && root->right)
        {
            if (root->iol)
            {
                // ft_init_io(root);
                exit_status = ft_app(root->iol, 0);
                if (exit_status)
                {
                    ft_reset_stds();
                    return exit_status;
                }
            }
            exit_status = ft_executer(root->right);
            ft_reset_stds();
        }
    }
    else if (root->type == OR_N)
    {
        exit_status = ft_executer(root->left);
        if (exit_status != 0 && root->right)
        {
            if (root->iol)
            {
                ft_init_io(root);
                exit_status = ft_app(root->iol, 0);
                if (exit_status)
                {
                    ft_reset_stds();
                    return exit_status;
                }
            }
            exit_status = ft_executer(root->right);
            ft_reset_stds();
        }
    }
    else
    {
        exit_status = ex_cmd(root);
    }
    ft_reset_stds();
    return (exit_status);
}




void execution()
{
    if (!neobash.tree)
        return;
    ft_before_exec(neobash.tree);
    neobash.status = ft_executer(neobash.tree);
}

