/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:46 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/21 16:56:54 by ytarhoua         ###   ########.fr       */
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


void	ft_errormsg(char *err, char *str, int ex)
{
	write(2, err, ft_strlen(err));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (ex >= 0)
		exit(ex);
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
	if (!ft_strncmp(data->line, "exit", ft_strlen(data->line)))
		ft_exit(0);
	paths = grep_paths(data->envp);
	cmdpath = get_cmd_path(data, paths, cmd[0]);
	if (!cmdpath)
		ft_errormsg("Neoshell: command not found: ", cmd[0], -1); //ls -la >>  **k [ls]-[-la]-[NULL] ---> /bin/ls -> execve(/bin/ls, k)
	else
	{
		pid = fork();
		if (!pid)
		{
			execve(cmdpath, cmd, data->envp);
		}
		else
				waitpid(pid,NULL, 0);
	}
}

void ft_coutquotes(t_data *data)
{
	int i;

	i = 0;
	data->dq = 0;
	data->sq = 0;
	while (data->line[i])
	{
		if (data->line[i] == 34)
			data->dq += 1;
		else if(data->line[i] == 39)
			data->sq += 1;
		i++;
	}
	if (data->sq % 2 != 0)
		ft_errormsg("neoshell :single qoute fiha mochkill", NULL, -1);
	if (data->dq % 2 != 0)
		ft_errormsg("neoshell :double qoute fiha mochkill", NULL, -1);
}



void neoshell(t_data *data)
{
		while(1)
		{
			data->line = readline(G "🌟::NeoShell~/💎[" ORG "Prompt" RES G "]🗿$\n|~↠$ " RES);
			if (data->line)
				add_history(data->line);
			ft_coutquotes(data);
			parseline(data);
			// ft_exec(data);
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
	{
		printf(ORG "Warrning :Please run it like this\n" RES);
		printf(CY"++++++++++++++++++++++$\n\v"RES);
		printf(G "bash-3.2$ ./minishell\n\v" RES);
		printf(CY"++++++++++++++++++++++$\n"RES);
	}

	return (0);
}