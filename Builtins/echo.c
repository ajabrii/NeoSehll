/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 14:57:33 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

int param(const char *s)
{
    int i = 0;

    if (s[i] != '-')
        return 0;

    i++;
    while (s[i] == 'n')
    {
        i++;
    }
    if (s[i] == '\0' || s[i] == ' ')
        return i;
    return 0;
}

void ft_echo(char *s)
{
    bool nl = true;
    bool sq = false;
    bool dq = false;
    int i;

    i = skip(s);
    while (param(&s[i]))
    {
        nl = false;
        i += param(&s[i]);
        i += skip(&s[i]);
    }

    if (i == 0)
        return;

    while (s[i])
    {
        if (s[i] == '\"' && !sq)
            dq = !dq;
        else if (s[i] == '\'' && !dq)
            sq = !sq;
        else
            printf("%c", s[i]);
        i++;
    }
    if (nl)
        printf("\n");
}
