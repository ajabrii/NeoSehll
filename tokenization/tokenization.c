/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/24 20:53:00 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	parseline(t_data *data)
{
	ft_lexical(data);

}


int ft_get(t_data *data, t_type **tokenslist, int i, int len ,t_token type)
{
	// this is lst_new function :
    t_type *token = malloc(sizeof(t_type));
    if (token == NULL)
        return (0);
	if (type == APP || type == PPA
	 || type == OR || type == AND)
    	token->value = ft_substr(data->line, i, 2);
	else if (type == RE || type == ER || type == PIP
        || type == OT || type == SQ || type == DQ)
		token->value =	ft_substr(data->line, i, 1);
    else
        token->value =	ft_substr(data->line, i, len);

	// printf("[\" %s \"]\n", token->value);
    token->type = type;
    token->next = NULL;

	//this is add_back function :
    ft_lstadd_backv2(tokenslist, token);
	return (1);
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
        tokenslist = tokenslist->next;
    }
    // sub[ntoken] = NULL;
}
