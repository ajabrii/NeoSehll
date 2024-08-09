/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:35:31 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 15:57:18 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

/*
lets say for exmple i have as a prompt 'unset PATH'
i need to split the prompt by \n to get the the siable name that
i should unset and basecly use the delone function to remove the node
*/

//TO DO

void del(void *full)
{
    free(full);
}

void ft_delone(t_env *lst, void (*del)(void*))
{
    if (!lst || !del)
        return;
    del(lst->key);
    del(lst->value);
    free(lst);
}

void ft_unset(char **s)
{
    // g_shell *neobash;
    t_env *envl = neobash.envl;
    t_env *tmp = envl;
    t_env *prev = NULL;
    int i = 1;

        // s += skip(s[1]);
        // printf ("str is ::%s||\n", s);
        if (!(s[i]))
            return;
        while (tmp)
        {
            i = 1;
            while (s[i])
            {
                if (!ft_strcmp(s[i], tmp->key) && ft_strcmp(s[i], "_"))
                {
                    printf("Here tmp->tmp ::%s \n", tmp->key);
                    if (prev)
                        prev->next = tmp->next;
                    else
                        neobash.envl = tmp->next;
                    ft_delone(tmp, del);
                    tmp = prev;
                    break;
                }
                i++;
            }
            prev = tmp;
            tmp = tmp->next;
        }
}

