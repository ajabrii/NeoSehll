/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:39:40 by kali              #+#    #+#             */
/*   Updated: 2024/08/09 16:29:35 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"


// bool ft_is_delimiter(char *delimiter, char *str)
// {
//     while (*str && *delimiter)
//     {
//         if (*delimiter == '"' || *delimiter == '\'')
//         {
//             char quote = *delimiter;
//             delimiter++;
//             while (*delimiter && *delimiter != quote)
//                 delimiter++;
//             if (*delimiter == quote)
//                 delimiter++;
//         }
//         else if (*str == *delimiter)
//         {
//             str++;
//             delimiter++;
//         }
//         else
//         {
//             return false;
//         }
//     }
//     while (*delimiter == '"' || *delimiter == '\'')
//         delimiter++;
//     return (!*delimiter && !*str);
// }

bool ft_is_delimiterv2(char *delimiter, char *str)
{
    while (*str && *delimiter)
    {
        if ((*delimiter == '"' || *delimiter == '\''))
        {
            neobash.exp_here = false;
            delimiter++;
        }
        if (*str == *delimiter)
        {
            str++;
            delimiter++;
        }
        else
            return false;
    }
    while (*delimiter == '"' || *delimiter == '\'')
        delimiter++;
    return (!*delimiter && !*str);
}
void heredoc_handler(int sig)
{
    if (sig == SIGINT)
    {
        neobash.status = 130;
        printf("\n");
        exit(130);
    }
}

void heredoc_f(t_io *io, int fd[2])
{
    char *line;

    signal(SIGINT, heredoc_handler);
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_is_delimiterv2(io->value, line))
        {
            free(line); // Free allocated memory
            break;
        }
        if (neobash.exp_here == true)
            ft_putstr_fd(expand_heredoc(line), fd[1]);
        else
            ft_putstr_fd(line, fd[1]);
        ft_putstr_fd("\n", fd[1]);
        free(line); // Free allocated memory
    }
    close(fd[1]); // Close write end after writing is done
    exit(0); // Ensure the child process exits
}
