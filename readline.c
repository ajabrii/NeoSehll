/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:46 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/11 13:32:06 by ytarhoua         ###   ########.fr       */
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
			data->line = readline(BL"YANeoShell >>$ "RES);
			edit_line(data);
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