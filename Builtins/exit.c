/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:01 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/31 18:31:29 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void    ft_exit(int ex)
{
    if (neobash.level > 1)
    {
        neobash.level -= 1;
        // printf("level d::%i\n", neobash.level);
        update_env("SHLVL", ft_itoa(neobash.level));
    }
    // ft_env(neobash.envl);
    // ft_free_all();
    exit(ex);
    printf("exit\n");
}
