/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Neotoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/21 17:01:46 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "neoshell.h"

bool is_whitespace(char line)
{
    if (line == ' ' || line == '\t' || line == '\v')
        return (true);
    return (false);
}

void	*ft_malloc(unsigned int size)
{
	void *res;

	res = malloc(size);
	if (!res)
		return (NULL);
	return (res);
}
bool ft_clean(char *line, int start, int end)
{
    while (start <= end)
    {
       if (is_whitespace(line[start]))
            return (false);
        start++;
    }
    return (true);
}

int ft_get(t_data *data, t_type **tokenslist, int i, int len ,t_token type)
{
	// this is lst_new function :
    static int qt;
    int start = 0;
    t_type *token = malloc(sizeof(t_type));
    if (token == NULL)
        return (0);
	if (type == APP || type == PPA || type == DQ
	 || type == OR || type == AND)
    	token->value = ft_substr(data->line, i, 2);
	else if (type == RE || type == ER || type == PIP
        || type == OT)
		token->value =	ft_substr(data->line, i, 1);
    else
        token->value =	ft_substr(data->line, i, len);
    if (type == DQ)
    {
        qt++;
        if (qt % 2)
            token->flag = ft_clean(data->line, start, i);
        start = i;
    }
    else 
        token->flag = true;
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

int check_red(t_data *data, t_type *tokenslist, int i)
{
    if (data->line[i] == '>' && data->line[i + 1] == '>')
        return (ft_get(data, &tokenslist, i, 0, APP));
    else if (data->line[i] == '<' && data->line[i + 1] == '<')
        return (ft_get(data, &tokenslist, i, 0, PPA));
    else if (data->line[i] == '&' && data->line[i + 1] == '&')
        return (ft_get(data, &tokenslist, i, 0, AND));
    else if (data->line[i] == '|' && data->line[i + 1] == '|')
    	return (ft_get(data, &tokenslist, i, 0, OR));
    else if (data->line[i] == '>')
        return (ft_get(data, &tokenslist, i, 0, RE));
    else if (data->line[i] == '<')
        return (ft_get(data, &tokenslist, i, 0, ER));
    else if (data->line[i] == '|')
        return (ft_get(data, &tokenslist, i, 0, PIP));
    else if (data->line[i] == '\"')
        return (ft_get(data, &tokenslist, i, 0, DQ));
    else if (data->line[i] == '\'')
        return (ft_get(data, &tokenslist, i, 0, SQ));
    else
        return (ft_get(data, &tokenslist, i, 0, OT));
    return (0);
}

int check_first(char *line, int i)
{
    if (line[i] == '>' && line[i + 1] == '>')
        return (2);
    else if (line[i] == '<' && line[i + 1] == '<')
        return (2);
    else if (line[i] == '&' && line[i + 1] == '&')
        return (2);
    else if (line[i] == '|' && line[i + 1] == '|')
    	return (2);
    else if (line[i] == '>')
        return (1);
    else if (line[i] == '<')
        return (1);
    else if (line[i] == '|')
        return (1);
    else if (line[i] == '\"')
        return (1);
    else if (line[i] == '\'')
        return (1);
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
            if (is_whitespace(data->line[i]))
            {
                len = count_whitespaces(data->line, i);
                 ft_get(data, &tokenslist, i, len, SP);
                i += len;
            }
            else if (check_first(data->line, i) == 2)
            {
                check_red(data, tokenslist, i);
                i += 2;
            }
            else
            {
                check_red(data, tokenslist, i);
                i++;
            }
        }
        else
        {
            start = i;
            while (!check_spcial(data->line[i]))
                i++;
			ft_get(data, &tokenslist, start, i - start, WR);
        }
    }
	while (tokenslist)
    {
        printf("{%s}\n", tokenslist->value);
        printf("{%d}\n", tokenslist->flag);
        tokenslist = tokenslist->next;
    }
    // sub[ntoken] = NULL;
}
