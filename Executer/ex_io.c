/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:42:59 by kali              #+#    #+#             */
/*   Updated: 2024/08/08 10:12:30 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

// void ft_init_io(t_node *root)
// {
//     pid_t pid;
//     t_io *io;

//     if (!root)
//         return;
//     root->args = ft_expand(root->args);

//     io = root->iol;
//     while (io)
//     {
//         if (io->type == HERE_DOC)
//         {
//             pipe(neobash.fd); // Create a pipe for heredoc
//             io->here_doc = neobash.fd[0];
//             printf("hello, %d\n", neobash.fd[0]);
//             pid = fork();
//             if (pid == 0)
//             {
//                 // Child process
//                 heredoc_f(io, neobash.fd);
//                 exit(0); // Exit child process
//             }
//             else
//             {
//                 // Parent process
//                 waitpid(pid, NULL, 0); // Wait for child process to complete
//                 close(neobash.fd[1]); // Close write end in parent
//             }
//         }
//         else
//         {
//             io->exp_val = ft_expand(io->value); // Expand other I/O values
//         }
//         io = io->next;
//     }
// }

void ft_init_io(t_node *root)
{
    pid_t pid;
    t_io *io;

    if (!root)
        return;
    root->args = ft_expand(root->args);

    io = root->iol;
    while (io)
    {
        if (io->type == HERE_DOC)
        {
            pipe(neobash.fd); // Create a pipe for heredoc
            io->here_doc = neobash.fd[0];
            pid = fork();
            if (pid == 0)
            {
                close(neobash.fd[0]); // Close read end in child
                heredoc_f(io, neobash.fd);
            }
            else
            {
                close(neobash.fd[1]); // Close write end in parent
                waitpid(pid, NULL, 0); // Wait for child process to complete
                io->here_doc = neobash.fd[0];
            }
        }
        else
        {
            io->exp_val = ft_expand(io->value); // Expand other I/O values
        }
        io = io->next;
    }
}


// void ft_init_io(t_node *root)
// {
//     pid_t pid;
//     t_io *io;

//     if (!root)
//         return;
//     root->args = ft_expand(root->args);
//         //    printf(RED"Hello\n"RES);

//     io = root->iol;
//     while (io)
//     {
//         // printf("[%s]-[%d]\n", io->value, io->type);
//         if (io->type == HERE_DOC)
//         {
//             // printf("Hello \n");
//             // neobash.hdoc = 0;
//             pipe(neobash.fd);
//             pid = fork();
//             if (!pid)
//             {
//                 heredoc_f(io, neobash.fd);
//                 io->here_doc = neobash.fd[0];
//                 exit(0);
//             }
//             else
//             {
//                 waitpid(pid, NULL, 0);
//                 close(neobash.fd[1]);
//                 close(neobash.fd[0]);
//             }
//         }
//         else
//         {
//             // printf("hello else\n");
//             io->exp_val = ft_expand(io->value);
//             // printf("hello else1\n");

//         }
//         io = io->next;
//     }
// }



int	ft_out(t_io *io, int flag)
{
	int		fd;

    if (!io->exp_val[0] || !io->exp_val)
    {

        ft_error("bash: $ : ambiguous redirect", io->value);
    	return (1);
    }
    fd = open(io->exp_val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_error("neobash: $: No such file or directory", io->exp_val);
        return (1);
    }
    if (!flag)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (ft_error("neobash : $ : problem", "dup2"), 1);
    }
    close(fd);
	return (0);
}

int	ft_in(t_io *io, int flag)
{
	int		fd;

    if (!io->exp_val[0] || !io->exp_val)
    {

        ft_error("bash: $ : ambiguous redirect", io->value);
    	return (1);
    }
    fd = open(io->exp_val, O_RDONLY);
	if (fd == -1)
    {
        ft_error("neobash: $: No such file or directory", io->exp_val);
        return (1);
    }
    if (!flag)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (ft_error("neobash : $ : problem", "dup2"), 1);
    }
    close(fd);
    return (0);
}

int	ft_app(t_io *io, int flag)
{
	int		fd;

    if (!io->exp_val[0] || !io->exp_val)
    {

        ft_error("bash: $ : ambiguous redirect", io->value);
    	return (1);
    }
    fd = open(io->exp_val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
    {
        ft_error("neobash: $: No such file or directory", io->exp_val);
        return (1);
    }
    if (!flag)
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (ft_error("neobash : $ : problem", "dup2"), 1);
    }
	close(fd);
	return (0);
}


int ft_io(t_node *root, int flag)
{
    t_io *tmp_io;
    int ex;

    tmp_io = root->iol;
    ex = 0;

    while (tmp_io)
    {
        if (tmp_io->type == OUT)
        {
            ex = ft_out(tmp_io, flag);
            if (ex)
                return (ex);
        }
        else if (tmp_io->type == IN)
        {
            ex = ft_in(tmp_io, flag);
            if (ex)
                return (ex);
        }
        else if (tmp_io->type == APP)
        {
            ex = ft_app(tmp_io, flag);
            if (ex)
                return (ex);
        }
        else if (tmp_io->type == HERE_DOC)
        {
            if (dup2(tmp_io->here_doc, STDIN_FILENO) == -1)
            {
                perror("dup2");
                return (1);
            }
            close(tmp_io->here_doc);
        }
        tmp_io = tmp_io->next;
    }
    return (0);
}
