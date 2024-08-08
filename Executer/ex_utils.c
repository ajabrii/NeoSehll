/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:58:23 by kali              #+#    #+#             */
/*   Updated: 2024/08/08 15:01:13 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}


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
    res = ft_malloc(sizeof(char *) * (ft_strlen(line) + 1));
    if (!res)
        return NULL;
    while (line[i])
    {
        while (line[i] && ft_isspace(line[i])) // don't forget to change this to libft functio ft_isspace !!!
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
            while (line[i] && !ft_isspace(line[i]))
                i++;
            res[nargs] = ft_substr(line, start, i - start);
        }
        // if (!res[nargs])
        // {
        //     while (nargs > 0)
        //         // free(res[--nargs]);
        //     free(res);
        //     return (NULL);
        // }
        nargs++;
    }
    res[nargs] = NULL;
    return (res);
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

char	*get_cmd_path(char **paths, char *cmd)
{
    // printf("`%s'\n", cmd);
    if (!cmd || !cmd[0])
        return (NULL);
    if (cmd[0] == '.')
    {
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		neobash.tmp = ft_strjoin(*paths, "/");
		neobash.palestine = ft_strjoin(neobash.tmp, cmd);
		// free(neobash.tmp);
		if (access(neobash.palestine, X_OK) == 0)
			return (neobash.palestine);
		// free(neobash.palestine);
		paths++;
	}
	return (NULL);
}
