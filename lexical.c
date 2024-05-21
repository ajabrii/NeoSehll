/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:16:25 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/21 21:10:36 by ajabri           ###   ########.fr       */
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

bool check_red_or_and(char *line, int i)
{
    if (line[i] == '>' && line[i + 1] == '>')
        return (true);
    else if (line[i] == '<' && line[i + 1] == '<')
        return (true);
    else if (line[i] == '|' && line[i + 1] == '|')
        return (true);
    else if (line[i] == '&' && line[i + 1] == '&')
        return (true);
    else
        return (false);
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
    int ntoken = 0;
    int len;


    data->sub = ft_malloc(sizeof(char *) * (ft_strlen(data->line) + 1));
    while (data->line[i])
    {

        if (check_spcial(data->line[i]))
        {
            if (is_whitespaces(data->line[i]))
            {
                len = count_whitespaces(data->line, i);
                data->sub[ntoken] = ft_substr(data->line, i, len);
                i += len;
            }
            else if (check_red_or_and(data->line, i))
            {
                data->sub[ntoken] = ft_substr(data->line, i, 2);
                i += 2;
            }
            else
            {
                data->sub[ntoken] = ft_substr(data->line, i, 1);
                i++;
            }
            ntoken++;
        }
        else
        {
            start = i;
            while (!check_spcial(data->line[i]))
                i++;
            data->sub[ntoken] = ft_substr(data->line, start, i - start);
            ntoken++;
        }
    }
    data->sub[ntoken] = NULL;
}

// static int check_qoute(t_data *data, int i)
// {
//     if (!ft_strncmp(data->sub[i], "\"", 1) || !ft_strncmp(data->sub[i], "'", 1))
//          return (0);
//     return (1);
// }

void set_flags(t_data *data)
{
    int i = 0;
    bool in_quotes = false;
    char quote_char = 0;
    bool has_whitespace = false;

    while (data->sub[i])
    {
        if (!in_quotes && (data->sub[i][0] == '"' || data->sub[i][0] == '\''))
        {
            in_quotes = true;
            quote_char = data->sub[i][0];
            has_whitespace = false;
        }
        else if (in_quotes && data->sub[i][0] == quote_char)
        {
            in_quotes = false;
            quote_char = 0;
        }
        else if (in_quotes && is_whitespaces(data->sub[i][0]))
            has_whitespace = true;
        if (in_quotes && has_whitespace)
        {
            int j = i;
            // Move backwards to set flags to false within the quotes
            while (j >= 0 && data->sub[j][0] != quote_char)
            {
                data->flags[j] = false;
                j--;
            }
            // Also set the flag of the starting quote to false
            if (j >= 0 && data->sub[j][0] == quote_char)
            {
                data->flags[j] = false;
            }
        }
        i++;
    }
}


t_token set_token(t_data *data, int i)
{
    if (!ft_strncmp(data->sub[i], ">", ft_strlen(data->sub[i])))
        return (RE);
    else if (!ft_strncmp(data->sub[i], "<", ft_strlen(data->sub[i])))
        return (ER);
    else if (!ft_strncmp(data->sub[i], ">>", ft_strlen(data->sub[i])))
        return (APP);
    else if (!ft_strncmp(data->sub[i], "<<", ft_strlen(data->sub[i])))
        return (HERDOC);
    else if (!ft_strncmp(data->sub[i], "\"", ft_strlen(data->sub[i])))
        return (DQ);
    else if (!ft_strncmp(data->sub[i], "'", ft_strlen(data->sub[i])))
        return (SQ);
    else if (!ft_strncmp(data->sub[i], "&&", ft_strlen(data->sub[i])))
        return (AND);
    else if (!ft_strncmp(data->sub[i], "||", ft_strlen(data->sub[i])))
        return (OR);
    else if (!ft_strncmp(data->sub[i], " ", 1)|| !ft_strncmp(data->sub[i], "  ", 1))
        return (SP);
    else if (!ft_strncmp(data->sub[i], "|", ft_strlen(data->sub[i])))
        return (PIP);
    else
    {
        if (data->sub[i][0] == '-')
            return (OPTION);
        return (WR);
    }
}

int ft_countv2(char **str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    give_token(t_data *data)
{
    t_type *head;
    int i;
    int sub_count = ft_countv2(data->sub);
    data->flags = (bool *)malloc(sizeof(bool) * (sub_count + 1));
    for (int j = 0; j < sub_count; j++) {
        data->flags[j] = true;
    }

    set_flags(data);

    i = 0;
    head = NULL;
    while (data->sub[i])
    {
        ft_lstadd_backv2(&head, ft_lstnewv2(data->sub[i], set_token(data, i), data->flags[i]));
        i++;
    }
    while (head)
    {
        printf("node[%s][%d]\n", head->value, head->flag);
        head = head->next;
    }
}
