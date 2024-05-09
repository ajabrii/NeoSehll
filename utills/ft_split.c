/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:40:29 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/09 16:13:27 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	wc;
	int	new;

	i = 0;
	wc = 0;
	new = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			new = 0;
		else if (new == 0)
		{
			new = 1;
			wc++;
		}
		i++;
	}
	return (wc);
}

static int	check_free(char **array, int j)
{
	if (array[j] == NULL)
	{
		while (j)
			free(array[j--]);
		free(array);
		return (1);
	}
	return (0);
}

static char	*arrays(const char **s, char c, int i)
{
	int		countll;
	int		j;
	char	*str;

	j = 0;
	countll = 0;
	while ((*s)[j] && (*s)[j] != c)
	{
		countll++;
		j++;
	}
	str = (char *)malloc(sizeof(char) * (countll + 1));
	if (!str)
		return (NULL);
	j = 0;
	while ((*s)[i] && j < countll)
	{
		str[j] = (*s)[i];
		j++;
		i++;
	}
	while (i--)
		(*s)++;
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		wc;
	int		j;

	if (s == NULL)
		return (NULL);
	j = 0;
	wc = count_words((char *)s, c);
	p = malloc(sizeof(char *) * (wc + 1));
	if (!p)
		return (NULL);
	while (*s && j < wc)
	{
		if (*s != c)
		{
			p[j] = arrays(&s, c, 0);
			if (check_free(p, j))
				return (NULL);
			j++;
		}
		s++;
	}
	p[wc] = 0;
	return (p);
}
