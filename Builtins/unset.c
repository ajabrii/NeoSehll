/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:35:31 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/05 11:42:12 by venom            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

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

void ft_delone(t_env *lst, void (*del)(void*))
{
    if (!lst || !del)
        return;
    del(lst->key);
    del(lst->value);
    free(lst);
}

void ft_unset(char *s)
{
    // g_shell *neobash;
    t_env *envl = neobash.envl;
    t_env *tmp = envl;
    t_env *prev = NULL;
    char **var;
    int i = 0;
    bool flag = false;

        s += skip(s);
        var = ft_split(s, ' ');
        printf ("str is ::%s||\n", s);
        if (!(*s))
            return;
        while (tmp)
        {
            i = 0;
            while (var[i])
            {
                if (!ft_strcmp(var[i], tmp->key))
                {
                    printf("Here tmp->tmp ::%s \n", tmp->key);
                    if (prev)
                        prev->next = tmp->next;
                    else
                        neobash.envl = tmp->next;
                    ft_delone(tmp, del);
                    flag = true;
                    tmp = prev;
                    break;
                }
                i++;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if (flag == false)
        {
        	ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_putstr_fd(s, 2);
        }
}
