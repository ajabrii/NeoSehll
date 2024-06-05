/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:29:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/05 11:01:21 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/utils.h"
#include "../HEADERS/neoshell.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	str = ft_malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memmove(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*dest;

	i = 0;
	dest = (char *)dst;
	s = (char *)src;
	if ((s == NULL && dst == NULL) || n == 0)
		return (dst);
	if (dest > s)
	{
		while (n--)
		{
			dest[n] = s[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strs;
	int		t_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	t_len = ft_strlen(s1) + ft_strlen(s2);
	strs = malloc((t_len + 1) * sizeof(char));
	if (!strs)
		return (NULL);
	ft_memmove(strs, s1, ft_strlen(s1));
	ft_memmove(strs + ft_strlen(s1), s2, ft_strlen(s2));
	strs[t_len] = '\0';
	return (strs);
}
