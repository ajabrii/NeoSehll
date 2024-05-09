/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Neotoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:12:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/09 17:02:05 by ytarhoua         ###   ########.fr       */
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
void	neo_token(t_data *data)
{
	int i;
	int j = 0;

	i = 0;
	data->arry = ft_malloc(sizeof(int) * ft_strlen(data->line, 0));
	char *str = ft_malloc((sizeof(char) * ft_strlen(data->line, 1)) + 1);
	while (data->line[i])
	{
		if (data->line[i] == '>' || data->line[i] == '<')
		{
			str[j] = ' ';
			if (data->line[i] == '>')
				str[++j] = '>';
			else if (data->line[i] == '<')
				str[++j] = '<';
			str[++j] = ' ';
			j++;
			i++;
		}
		str[j] = data->line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	printf("%s\n", str);
	
}