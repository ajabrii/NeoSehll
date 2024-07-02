/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/02 12:54:58 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

int skip_spaces(char *str)
{
    int i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == 'n'))
        i++;
    if (str[i] == NULL)
        return (NULL);
    return (i);
}

void ft_echo(char *s)
{
    g_shell *data;
    bool nl = false;
    int i = 0;

    if (!ft_strncmp(s, "-n", 2))
        nl = true;
    i += 4;
    skip_spaces(&s[i]);
}