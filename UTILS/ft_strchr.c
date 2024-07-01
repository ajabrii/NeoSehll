/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:20:32 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/06/30 16:57:16 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/utils.h"

int	ft_strchr(const char *s, int c)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (s[z])
		z++;
	while (i <= z)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}
