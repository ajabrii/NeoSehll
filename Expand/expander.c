/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:19:27 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/06 11:37:01 by venom            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*ft_expand(char *str)
{
	char *res;
	int	i = 0;

	res = ft_strdup("");
	if (!str)
		return (NULL);
	while (str[i])
	{
		// printf("here\n");
		if (str[i] == '\'')
			res = ft_strjoin(res, handle_squotes(str, &i));
		else if (str[i] == '"' || str[i] == '`')
			res = ft_strjoin(res, handle_dquotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin(res, handle_dollar(str, &i));
		else
			res = ft_strjoin(res, normal_str(str, &i));
	}
	return (res);
}

//i have to put last char** that was executed to update that ('_') var.
//when i write that cmd on my shell -> $_ so i have to execute last cmd.
