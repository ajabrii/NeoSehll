/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:55:37 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 10:00:08 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*heredoc_exp(char *str)
{
	char *res;
	int	i = 0;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '`' || str[i] == '\'')
			res = ft_strjoin(res, handle_dquotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin(res, handle_dollar(str, &i));
		else
			res = ft_strjoin(res, normal_str(str, &i));
	}
	return (res);
}