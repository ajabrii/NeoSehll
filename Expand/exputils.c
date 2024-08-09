/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exputils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:55:46 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 10:03:26 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char *normal_str(char *str, int *i)
{
	int start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"'
	&& str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *handle_squotes(char *str, int *i)
{
	int start = *i;

	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *handle_dquotes(char *str, int *i)
{
	char *res;
	char qoute;

	qoute = str[*i];
	res = ft_strdup("\"");
	(*i)++;
	while (str[*i] != qoute)
	{
		if (str[*i] == '$')
			res = ft_strjoin(res, handle_dollar(str, i));
		else
			res = ft_strjoin(res, dquote_str(str, i, qoute));
	}
	(*i)++;
	return (ft_strjoin(res, "\""));
}

char	*dquote_str(char *str, int *i, char qoute)
{
	int	start;

	start = *i;
	while (str[*i] != qoute && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dollar(char *str, int *i)
{
	int		start;
	char	*var;
	char	*value;

	// printf("str is ::%s\n", &str[*i]);
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		// printf("here\n");
		return (ft_itoa(neobash.status)); //here i have to put exit status
	}
	else if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (normal_str(str, i));
	}
	else if (str[*i] == '$')
	{
		(*i)++;
		return (ft_substr(str, *i - 2, 2));
	}
	else if (!valid_char(str[*i]))
	{
		printf("invalid var\n");
		return (ft_strdup(""));
	}
	start = *i;
	// printf("%i\n", (*i));
	while (valid_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	// printf("here is it ::%s\n", var);
	value = get_env_val(var);
	if (!value)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(value));
}

bool	valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
