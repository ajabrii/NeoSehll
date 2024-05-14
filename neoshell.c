/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:46 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/14 19:10:25 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "neoshell.h"

void	get_neoenvp(t_list **lst, t_data *data)
{
	int i;
	t_list *tmp;

	i = -1;
	tmp = (*lst);

	while (data->envp[++i])
	{
		ft_lstadd_back(lst, ft_lstnew(data->envp[i]));
	}
	data->env_size = i;
}

void	get_init(char **envp, t_data *data)
{
	t_list *lst;

	lst = NULL;
	data->envp = envp;
	data->line = NULL;
	get_neoenvp(&lst, data);
}

void ft_exec(t_data *data)
{
	char **paths;
	char **cmd;
	char *cmdpath;
	int pid;

	cmd = ft_split(data->line, ' ');
	if (!cmd[0])
		return;
	if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		exit(0);
	paths = grep_paths(data->envp);
	cmdpath = get_cmd_path(data, paths, cmd[0]);
	pid = fork();
	if (!pid)
		execve(cmdpath, cmd, data->envp);
	else
		wait(NULL);
}

void neoshell(t_data *data)
{
		while(1)
		{
			// data->line = readline(G "🌟::NeoShell~/💎["RES ORG"Prompt"RES G"]🗿$\n|~↠$ "RES);
			data->line = readline(G "neoshell>>>>$ " RES);
			// parseline(data);
			ft_exec(data);
			free(data->line);
		}
}
int main(int ac, char **av, char **envp)
{

	t_data data;

	(void)av;
	if (ac == 1)
	{
		get_init(envp, &data);
		neoshell(&data);
	}
	else
		printf(RED"Warrning :Pls enter ./minishell :(\n"RES);
	return (0);
}