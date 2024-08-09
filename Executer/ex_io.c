/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:42:59 by kali              #+#    #+#             */
/*   Updated: 2024/08/09 10:06:50 by ytarhoua         ###   ########.fr       */
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
    root->args = heredoc_exp(root->args);

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
    int     ex;

    ex = 0;
    // printf(RED"Hello\n"RES);
    // if (!io->expanded_value || io->expanded_value[1])
    // {
    // 	ex = ft_err_msg(
    // 			(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
    // 	return (*status);
    // }
    fd = open(io->exp_val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    printf(ORG"{``%d''}\n"RES, fd);
    if (fd == -1)
    {
		ft_putstr_fd("neobash: value: Permission denied\n", 2);
        ex = 1;
        return (ex);
	}
   if (!flag)
    {
        dup2(fd, STDOUT_FILENO);
        // dup2(fd, STDERR_FILENO); // Redirect stderr as well
    }
    printf("Here\n");
	close(fd);
	ex = 0;
	return (ex);
}

int	ft_in(t_io *io, int flag)
{
	int		fd;
    int     ex;

    ex = 0;
    // if (!io->expanded_value || io->expanded_value[1])
    // {
    // 	ex = ft_err_msg(
    // 			(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
    // 	return (*status);
    // }
    fd = open(io->exp_val, O_RDONLY);
	if (fd == -1)
	{
        ft_putstr_fd("neobash: value: Permission denied\n", 2);
        ex = 1;
        return (ex);
    }
    if (!flag)
	    dup2(fd, STDIN_FILENO);
	close(fd);
	ex = 0;
	return (ex);
}

int	ft_app(t_io *io, int flag)
{
	int		fd;
    int     ex;

    ex = 0;
    // if (!io->expanded_value || io->expanded_value[1])
    // {
    // 	ex = ft_err_msg(
    // 			(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
    // 	return (*status);
    // }
    fd = open(io->exp_val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
        // ex = ft_err_msg(ft_check_write(io->value)); msg
        printf("neobash: %s: Permission denied\n",io->value); // exp_val
        ex = 1;
        return (ex);
    }
    if (!flag)
    {
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO); // Redirect stderr as well
    }
	close(fd);
	ex = 0;
	return (ex);
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
                return ex;
        }
        else if (tmp_io->type == IN)
        {
            ex = ft_in(tmp_io, flag);
            if (ex)
                return ex;
        }
        else if (tmp_io->type == APP)
        {
            ex = ft_app(tmp_io, flag);
            if (ex)
                return ex;
        }
        else if (tmp_io->type == HERE_DOC)
        {
            if (dup2(tmp_io->here_doc, STDIN_FILENO) == -1)
            {
                perror("dup2");
                return 1;
            }
            close(tmp_io->here_doc); // Close the read end after redirection
        }
        tmp_io = tmp_io->next;
    }
    return 0;
}

// int ft_io(t_node *root, int flag)
// {
//     t_io *tmp_io;
//     int ex;

//     tmp_io = root->iol;
//     ex = 0;

//     while (tmp_io)
//     {
//         if (tmp_io->type == OUT)
//         {
//             ex = ft_out(tmp_io, flag);
//             if (ex)
//                 return ex;
//         }
//         else if (tmp_io->type == IN)
//         {
//             ex = ft_in(tmp_io, flag);
//             if (ex)
//                 return ex;
//         }
//         else if (tmp_io->type == APP)
//         {
//             ex = ft_app(tmp_io, flag);
//             if (ex)
//                 return ex;
//         }
//         else if (tmp_io->type == HERE_DOC)
//         {
//             printf("hello, %d\n", tmp_io->here_doc);
//             if (dup2(tmp_io->here_doc, STDIN_FILENO) == -1)
//             {
//                 printf(RED"hello\n"RES);
//                 perror("dup2");
//                 return 1;
//             }
//             close(tmp_io->here_doc); // Close the read end after redirection
//         }
//         tmp_io = tmp_io->next;
//     }
//     return 0;
// }


// int ft_io(t_node *root, int flag)
// {
//     t_io *tmp_io;
//     int ex;

//     tmp_io = root->iol;
//     ex = 0;

//     while (tmp_io)
//     {
//         if (tmp_io->type == OUT)
//         {
//             ex = ft_out(tmp_io, flag);
//             if (ex)
//                 return (ex);
//         }
//         else if (tmp_io->type == IN)
//         {
//             ex = ft_in(tmp_io, flag);
//             if (ex)
//                 return (ex);
//         }
//         else if (tmp_io->type == APP)
//         {
//             ex = ft_app(tmp_io, flag);
//             if (ex)
//                 return (ex);
//         }
//         else if (tmp_io->type == HERE_DOC)
// 			(dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
//         tmp_io = tmp_io->next;
//     }
//     return (0);
// }
