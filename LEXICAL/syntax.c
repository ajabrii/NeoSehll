/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:20:20 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/05 15:26:42 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HEADERS/neoshell.h"
# include "../HEADERS/utils.h"

int ft_block_size(t_block *block)
{
    t_block *tmp;
    int i;

    tmp = block;
    i = 0;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}
void ft_syntax()
{
    t_block *tmp;

    tmp = shell.block;
    
    while (tmp)
    {

    }
}