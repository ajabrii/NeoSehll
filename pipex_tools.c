/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:36:21 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/15 15:24:28 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neoshell.h"

// static void	ft_msg(char *av, char *err)
// {
// 	write(2, err, ft_strlen(err));
// 	write(2, av, ft_strlen(av));
// 	write(2, "\n", 1);
// }

char	**grep_paths(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_data *pp, char **paths, char *cmd)
{
	if (cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		pp->tmp = ft_strjoin(*paths, "/");
		pp->palestine = ft_strjoin(pp->tmp, cmd);
		free(pp->tmp);
		if (access(pp->palestine, X_OK) == 0)
			return (pp->palestine);
		free(pp->palestine);
		paths++;
	}
	return (NULL);
}

// void	ft_openf(t_ppx *pp, int flag)
// {
// 	if (flag == 2)
// 	{
// 		pp->fd2 = open(pp->av[pp->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
// 		if (pp->fd2 < 0)
// 		{
// 			ft_msg(pp->av[4], "zsh: permission denied: ");
// 			exit(1);
// 		}
// 	}
// 	else if (flag == 1)
// 	{
// 		if (access(pp->av[1], R_OK))
// 		{
// 			ft_msg(pp->av[1], "zsh: permission denied: ");
// 			exit(0);
// 		}
// 		else
// 		{
// 			pp->fd1 = open(pp->av[1], O_RDONLY);
// 			if (pp->fd1 < 0)
// 				ft_msg(pp->av[1], "zsh: no such file or directory: ");
// 		}
// 	}
// }
