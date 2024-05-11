/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Neotoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/11 15:23:50 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "neoshell.h"

// out ====> arry [CMD,SP,RE,SP, WR]
// CMD WR >> access() > open >> os append PIP
int ft_strlen(char *str, int flag)
{
	int i = -1;
	int size;
	
	size = 0;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (flag)
				size+= 2;
		}
	}
	return (i + size);
}

void	*ft_malloc(unsigned int size)
{
	void *res;

	res = malloc(size);
	if (!res)
		return (NULL);
	return (res);
}

//ls>out
//ls 

int is_special(char *str)
{
	int i;

	i = 0;
	printf("{%s}\n\n",str);
	if (!ft_strncmp(str, ">>", 2))
		i = 2;
	else if (!ft_strncmp(str, "<<", 2))
		i = 3;
	else if (!ft_strchr(str, '>') || ft_strchr(str, '<'))
		i = 1;
	return (i);
}

int find_index(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (2);
	return (0);
}

void ft_strcpy(char *dst, char *src)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (src[i])
	{
		dst[j] = src[i];
		i++;
		j++; 
	}
}

void edit_redi(t_data *data)
{
	int i = 0;
	int j = 0;
	data->linev2 = ft_malloc((sizeof(char) * ft_strlen(data->line, 1)) + 1);
	while (data->line[i])
	{
		while (data->line[i] == ' ')
			i++;
		if (find_index(data->line[i]))
		{
			data->linev2[j] = ' ';
			if (is_special(&data->line[i]) == 2)
			{
				data->linev2[++j] = '>';
				data->linev2[++j] = '>';
				i++;
			}
			else if (is_special(&data->line[i]) == 3)
			{
				data->linev2[++j] = '<';
				data->linev2[++j] = '<';
				i++;
			}
			else if (find_index(data->line[i]) == 1)
				data->linev2[++j] = '>';
			else if (find_index(data->line[i]) == 2)
				data->linev2[++j] = '<';
			data->linev2[++j] = ' ';
			j++;
			i++;
		}
		data->linev2[j] = data->line[i];
		i++;
		j++;
	}
	data->linev2[j] = '\0';
}
void	edit_line(t_data *data)
{
	int i;

	i = 0;
	data->arry = ft_malloc(sizeof(int) * ft_strlen(data->line, 0));
	edit_redi(data,"","");
	
	printf(".......%s\n", data->linev2);
}