/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:10:32 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/01 20:19:37 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HEADERS/neoshell.h"
# include "../HEADERS/utils.h"

/*
lets say for exmple i have as a prompt 'unset PATH'
i need to split the prompt by \n to get the the variable name that
i should unset and basecly use the delone function to remove the node
*/

//TO DO

void del(void *full)
{
    free(full);
}

void ft_delone(t_envl *lst, void (*del)(void*))
{
    if (!lst || !del)
        return;
    del(lst->envar);
    del(lst->value);
    free(lst);
}

void ft_unset(char *s)
{
    g_neo *data;
    t_envl *envl = data->envl;
    t_envl *tmp = envl;
    t_envl *prev = NULL;

    // if there is spaces skip them here;
    if (!ft_strncmp(s, "unset", 5))
    {
        s += 5;
        while (tmp)
        {
            if (!ft_strncmp(s, tmp->envar, ft_strlen(s)))
            {
                if (prev)
                    prev->next = tmp->next;
                else
                    data->envl = tmp->next;
                ft_delone(tmp, del);
                return;
            }
            else
            {
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }
}
