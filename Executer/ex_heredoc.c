/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:39:40 by kali              #+#    #+#             */
/*   Updated: 2024/08/09 14:13:15 by ytarhoua         ###   ########.fr       */
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
                delimiter++;
        }
        if (*str == *delimiter)
        {
            str++;
            delimiter++;
        }
        else
        {
            return false;
        }
    }
    while (*delimiter == '"' || *delimiter == '\'')
        delimiter++;
    return (!*delimiter && !*str);
}


void heredoc_f(t_io *io, int fd[2])
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        printf("delemiter is ::%s and line is ::%s\n", io->value, line);
        if (ft_is_delimiterv2(io->value, line))
        {
            free(line); // Free allocated memory
            break;
        }
        ft_putstr_fd(line, fd[1]);
        ft_putstr_fd("\n", fd[1]);
        free(line); // Free allocated memory
    }
    close(fd[1]); // Close write end after writing is done
    exit(0); // Ensure the child process exits
}


// bool	ft_is_delimiter(char *delimiter, char *str)
// {
// 	while (*str)
// 	{
// 		if (*delimiter == '"' || *delimiter == '\'')
// 		{
// 			delimiter++;
// 			continue ;
// 		}
// 		else if (*str == *delimiter)
// 		{
// 			str++;
// 			delimiter++;
// 		}
// 		else
// 			return (false);
// 	}
// 	while (*delimiter == '"' || *delimiter == '\'')
// 		delimiter++;
// 	return (!*delimiter);
// }


// void heredoc_f(t_io *io, int fd[2])
// {
//     char *line;
//     char *quotes;

//     quotes = io->value;
//     while (*quotes && *quotes != '"' && *quotes != '\'')
//         quotes++;

//     while (1)
//     {
//         line = readline("> ");
//         if (!line)
//             break;
//         if (ft_is_delimiter(io->value, line))
//         {
//             printf("`%s'\n", io->value);
//             free(line); // Free allocated memory
//             break;
//         }
//         ft_putstr_fd(line, fd[1]);
//         ft_putstr_fd("\n", fd[1]);
//         free(line); // Free allocated memory
//     }
//     close(fd[1]); // Close write end after writing is done
// }

// void	heredoc_f(t_io *io, int fd[2])
// {
// 	char	*line;
// 	char	*quotes;

// 	quotes = io->value;
// 	while (*quotes && *quotes != '"' && *quotes != '\'')
// 		quotes++;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_is_delimiter(io->value, line))
// 			break ;
// 		else
// 		{
// 			ft_putstr_fd(line, fd[1]);
// 			ft_putstr_fd("\n", fd[1]);
// 			close(neobash.fd[0]);
// 		}
// 	}
//     // close(fd[1]);
//     // leaks
//     // exit(0);
// }


/********
 *
 *
 *
 * *********/

