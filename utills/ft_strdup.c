/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:20:43 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/05/09 15:12:58 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*p;

	len = 0;
	while (s[len] != '\0')
		len++;
	p = malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
	{
		p[len] = s[len];
		len++;
	}
	p[len] = '\0';
	return (p);
}
