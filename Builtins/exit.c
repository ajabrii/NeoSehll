/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:01 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/31 18:55:12 by venom            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

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

void    ft_exit(char *str)
{
    int status = neobash.status;
    int i = 0;

    i = skip(str);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            i++;
        else
            break;   
    }
    if (!str[i])
        status = ft_atoi(str);
    // t_putstr_fd("exit\n", 1);
    if (out_of_range(str))
	{
		// print_exit_error(str);
		exit(2);
	}
    // ft_free_all();
    exit(status);
}
