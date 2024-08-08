/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:28 by kali              #+#    #+#             */
/*   Updated: 2024/08/08 14:21:29 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_free_all()
{
    t_leak *current = neobash.leaks;
    t_leak *next;

    while (current != NULL)
    {
        // printf("RED[%p]",current->address);
        next = current->next;
        free(current->address);
        free(current);
        current = next;
    }
    neobash.leaks = NULL;
    rl_clear_history();
}
