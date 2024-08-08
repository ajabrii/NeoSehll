/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:59:15 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/08 11:00:38 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	ft_export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void print_ex(t_env *env)
{
    neobash.envl_dup = env_list_dup(env);
	t_env *env_dup = neobash.envl_dup;
    if (!env_dup)
    {
        printf("Failed to duplicate environment list.\n");
        return;
    }
    sort_env(env_dup);
    while (env_dup)
    {
        printf("declare -x %s", env_dup->key);
        if (env_dup->value)
            printf("=\"%s\"\n", env_dup->value);
        else
            printf("\n");
        env_dup = env_dup->next;
    }
	//i have to free here because i dup the list every time i enter export without args;
}

t_env *env_list_dup(t_env *env)
{
    t_env *new_head = NULL;
    t_env *new_tail = NULL;
    t_env *new_node;

    while (env)
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return NULL;
        new_node->key = strdup(env->key);
        new_node->value = env->value ? strdup(env->value) : NULL;
        new_node->next = NULL;

        if (!new_head)
        {
            new_head = new_node;
            new_tail = new_node;
        }
        else
        {
            new_tail->next = new_node;
            new_tail = new_node;
        }
        env = env->next;
    }
    return new_head;
}

void ft_swap(t_env *a, t_env *b, int *swapped)
{
    char *temp_key;
    char *temp_value;

    temp_key = a->key;
    temp_value = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = temp_key;
    b->value = temp_value;
    *swapped = 1;
}

void	sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*p;
	t_env	*d;
	int		swapped;

	tmp = env;
	if (!tmp)
		return ;
	while (1)
	{
		swapped = 0;
		p = tmp;
		while (p->next)
		{
			d = p->next;
			if (ft_strcmp(p->key, d->key) > 0)
				ft_swap(p, d, &swapped);
			// printf("%s=%s\n", p->key, p->value);
			p = p->next;
		}
		if (!swapped)
			break ;
	}
}
