/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neoshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:46 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/13 21:52:30 by ajabri           ###   ########.fr       */
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
void neoshell(t_data *data)
{
		while(1)
		{
			data->line = readline(G "🌟::NeoShell~/💎["RES ORG"Prompt"RES G"]🗿>\n|~↠$ "RES);
			parseline(data);
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