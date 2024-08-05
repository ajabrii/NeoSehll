/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:58:23 by kali              #+#    #+#             */
/*   Updated: 2024/08/05 06:44:13 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
# include "../Header/headers.h"

char **get_cmdagrs(char *line)
{
    char **res;
    int i;
    int start;
    // int len;
    char q;
    int nargs;

    i = 0;
    nargs = 0;
    res = malloc(sizeof(char *) * (ft_strlen(line) + 1));
    if (!res)
        return NULL;
    while (line[i])
    {
        while (line[i] && isspace(line[i])) // don't forget to change this to libft functio ft_isspace !!!
            i++;
        if (line[i] == '\0')
            break;

        if (line[i] == '\"' || line[i] == '\'')
        {
            q = line[i];
            i++;
            start = i;
            while (line[i] && line[i] != q)
                i++;
            if (line[i] == q)
                i++;
            res[nargs] = ft_substr(line, start, i - start - 1);
        }
        else
        {
            start = i;
            while (line[i] && !isspace(line[i]))
                i++;
            res[nargs] = ft_substr(line, start, i - start);
        }
        // if (!res[nargs])
        // {
        //     return NULL;
        // }
        nargs++;
    }
    res[nargs] = NULL;
    return res;
}

int ft_count_size()
{
	int i;

	i = 0;
	while (neobash.envp[i])
		i++;
	return (i);
}

char **get_my_envp()
{
	int i;
	char **res;
	t_env *tmpl;
	int lsize;

	lsize = ft_count_size() + 1; // change the count_size withe the list_size !!!
	res = ft_malloc(sizeof(char *) * lsize);
	i = 0;
	tmpl = neobash.envl;
	while (tmpl)
	{
		res[i] = ft_strjoinc(tmpl->key, tmpl->value, '=');
		i++;
		tmpl = tmpl->next;
	}
	res[i] = NULL;
	return (res);
}