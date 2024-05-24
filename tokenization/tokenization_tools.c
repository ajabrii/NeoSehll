/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:38:47 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/24 20:58:05 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool is_whitespace(char line)
{
    if (line == ' ' || line == '\t' || line == '\v')
        return (true);
    return (false);
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