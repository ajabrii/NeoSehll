/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:01 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/09 12:29:29 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

//still shell level --
//i have to skip zeros btw, i need a simpel function to loop for zeros.

int is_positive(char  *str)
{
    const char	*limit = "9223372036854775807";
    int len = 0;

    if (*str == '+')
        str++;
    len = ft_strlen(str);
    if (len > 19)
        return (1);
    if (len == 19 && (ft_strcmp(str, limit) > 0))
        return (1);
    return (0);
}

int out_of_range(char *str)
{
    // if (*str == '-')
    //     return (is_negative(str + 1));
    return (is_positive(str));
}

void   ft_exit(char **str)
{
    int status = neobash.status;
    int i = 0;
    int c = 1;

    if (neobash.level > 1)
    {
        neobash.level -= 1;
        update_env("SHLVL", ft_itoa(neobash.level));
    }
    if(count_args(str) == 1)
    {
        ft_free_all();
        exit(0);
    }
    if (count_args(str) > 2)
    {
        ft_error("neobash: exit: too many arguments", NULL);
        neobash.status = 1;
        return;
    }
    // i = skip(str[c]);
    // printf("str '%s'\n", str);
    while (str[c][i])
    {
        if (!ft_isdigit(str[c][i]))
            i++;
        else
            break;
    }
    if (!str[c][i])
        status = ft_atoi(str[c]);
    // t_putstr_fd("exit\n", 1);
    if (out_of_range(str[c]))
	{
		// print_exit_error(str);
        ft_free_all();
		exit(2);
	}
    ft_free_all();
    printf("exit : %i\n", status);
    exit(status);
}
