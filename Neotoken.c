/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Neotoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/21 12:30:25 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "neoshell.h"

void	*ft_malloc(unsigned int size)
{
	void *res;

	res = malloc(size);
	if (!res)
		return (NULL);
	return (res);
}

int ft_get(t_data *data, t_type **tokenslist, int i, t_token type)
{
	int n = 0;
	// this is lst_new function :
    t_type *token = malloc(sizeof(t_type));
    if (token == NULL)
        return (0);
	if (type == APP || type == PPA || type == DQ
	 || type == OR || type == AND)
	 {
    	token->value = ft_substr(data->line, i, 2);
		n = 2;
	 }
	else if (type == RE || type == ER || type == PIP)
	{
		token->value =	ft_substr(data->line, i, 1);
		n = 1;
	}
	// printf("[\" %s \"]\n", token->value);
    token->type = type;
    token->next = NULL;

	//this is add_back function :
    ft_lstadd_backv2(tokenslist, token);
	return (n);
}


int ft_word(t_data *data, t_type **tokenslist, int i, int len, t_token type)
{
	// this is lst_new function :
    t_type *token = malloc(sizeof(t_type));
    if (token == NULL)
        return (0);

	token->value =	ft_substr(data->line, i, len);
	// printf("[\" %s \"]\n", token->value);
    token->type = type;
    token->next = NULL;

	//this is add_back function :
    ft_lstadd_backv2(tokenslist, token);
	return (1);
}

void	parseline(t_data *data)
{
	int i;
	i = 0;
	data->arry = ft_malloc(sizeof(int) * ft_strlen(data->line));
	// ft_coutquotes(data);
	ft_lexical(data);

	// edit_redi(data);
}

bool check_spcial(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return (false);
    if (c >= '0' &&  c <= '9')
        return (false);
    if (c == 45)
        return (false);
    return (true);
}

int ft_count(char **str)
{
    int i = 0;
    if(!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int check_red_or_and(t_data *data, t_type *tokenslist, int i)
{
    if (data->line[i] == '>' && data->line[i + 1] == '>')
        return (ft_get(data, &tokenslist, i, APP));
    else if (data->line[i] == '<' && data->line[i + 1] == '<')
        return (ft_get(data, &tokenslist, i, PPA));
    else if (data->line[i] == '&' && data->line[i + 1] == '&')
        return (ft_get(data, &tokenslist, i, AND));
    else if (data->line[i] == '|' && data->line[i + 1] == '|')
    	return (ft_get(data, &tokenslist, i, OR));
    else if (data->line[i] == '>')
        return (ft_get(data, &tokenslist, i, RE));
    else if (data->line[i] == '<')
        return (ft_get(data, &tokenslist, i, ER));
    else if (data->line[i] == '|')
        return (ft_get(data, &tokenslist, i, PIP));
    else if (data->line[i] == '\"')
        return (ft_get(data, &tokenslist, i, DQ));
    else if (data->line[i] == '\'')
        return (ft_get(data, &tokenslist, i, SQ));
    else
        return (0);
}

// if_space() -> append_space()
// ifis -> > < >> << | || && ) ( append_spcials()
// ifis ->word or any thing $" '

int count_whitespaces(char *line, int i)
{
    int count;

    count = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
    {
        i++;
        count += 1;
    }
    return (count);
}

bool is_whitespaces(char line)
{
    if (line == ' ' || line == '\t' || line == '\v')
        return (true);
    return (false);
}

void ft_lexical(t_data *data)
{
    int i;

    i = 0;
    int start = 0;
    int len;
	t_type *tokenslist;
	tokenslist = NULL;

    while (data->line[i])
    {
        if (check_spcial(data->line[i]))
        {
            if (is_whitespaces(data->line[i]))
            {
                len = count_whitespaces(data->line, i);
                // sub[ntoken] = ft_substr(data->line, i, len);
                i += len;
            }
            else if (check_red_or_and(data, tokenslist, i) == 2)
                i += 2;
            else if (check_red_or_and(data , tokenslist, i) == 1)
                i++;
        }
        else
        {
            start = i;
            while (!check_spcial(data->line[i]))
                i++;
			ft_word(data, &tokenslist, start, i - start, WR);
        }
    }
	while (tokenslist)
    {
        printf("{%s}\n", tokenslist->value);
        tokenslist = tokenslist->next;
    }
    // sub[ntoken] = NULL;
}
