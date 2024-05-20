/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lixical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:16:25 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/20 21:12:17 by ajabri           ###   ########.fr       */
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
    char **sub;

    sub = ft_malloc(sizeof(char *) * ft_strlen(data->line));
    while (data->line[i])
    {

        if (check_spcial(data->line[i]))
        {
            if (is_whitespaces(data->line[i]))
            {
                len = count_whitespaces(data->line, i);
                sub[ntoken] = ft_substr(data->line, i, len);
                printf("[%s]\n", sub[ntoken]);
                i += len;
            }
            else if (check_red_or_and(data->line, i))
            {
                sub[ntoken] = ft_substr(data->line, i, 2);
                printf("[%s]\n", sub[ntoken]);
                i += 2;
            }
            else
            {
                sub[ntoken] = ft_substr(data->line, i, 1);
                printf("[%s]\n", sub[ntoken]);
                i++;
            }
            ntoken++;
        }
        else
        {
            start = i;
            while (!check_spcial(data->line[i]))
                i++;
            sub[ntoken] = ft_substr(data->line, start, i - start);
            printf("[%s]\n", sub[ntoken]);
            ntoken++;
        }
    }
    // sub[ntoken] = NULL;
}
