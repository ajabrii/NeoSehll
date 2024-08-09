/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:58:48 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 16:41:06 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char *handle_q(char *line, int start)
{
    char *res;
    int i;
    char q;

    i = start;
    res = ft_malloc(sizeof(char) * (ft_strlen(&line[start]) + 1));

    if (!res)
        return NULL;
    if (line[i] == '\0')
	{
		res[i] = '\0';
        return (res);
	}
	res = ft_strdup("");
	while (line[i] && !isspace(line[i])) // dont forget to change this !!
	{
    	if (line[i] == '"' || line[i] == '\'')
        	{
				res = ft_strjoin(res, ft_substr(line, start, i - start));
            	q = line[i];
            	i++;
				start = i;
				// printf("start is ::%i\n", start);
            	while (line[i] && line[i] != q)
                	i++;
            	if (line[i] == q)
                	i++;
            	res = ft_strjoin(res, ft_substr(line, start, i - start - 1));
				printf("CHOOOOF::%s\n", res);
				printf("here-----------------\n");
				start = i;
				if (!line[i]) //this for (export test="");
					break;
				// printf("--------------------------------->>>>>>>>>>>>>>%s\n", res);
        	}
			i++;
		if (!line[i] || isspace(line[i])) // dont forgetto change this!!
            	res = ft_strjoin(res, ft_substr(line, start, i - start));
	}
	if (line[i] == ' ')
		i++;
	printf("LOOK :: %s\n",res);
	neobash.count = i;
    return res;
}


int	parse_key(char *str)
{
	int	i;

	i = 0;
	neobash.count = 0;
	// printf("str is ::%s::\n", str);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
    i++;
	while (str[i] && str[i] != '='
	&& str[i] != ' ' && str[i] != '"'
	&& str[i] != '\'')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (0);
		else if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_key(char *str)
{
	int	i;
	i = 0;
	neobash.count = 0;
	neobash.app = false;
	// printf("string is ::%s\n", str);
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "+=", 2))
		{
			neobash.app = true;
			neobash.count = i + 2;
			// printf("hereeeeee:::%s\n", ft_substr(str, 0, i));
			return (ft_substr(str, 0, i));
		}
		else if (str[i] == '=' || str[i] == ' ')
		{
			neobash.count = i + 1;
			// printf ("here\n");
			return (ft_substr(str, 0, i));
		}
		i++;
	}
	neobash.count = i;
	// printf("i is ::%i\n", neobash.count);
	return (ft_strdup(str));
}

bool search_env(char *s)
{
    t_env *env = neobash.envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strcmp(s, tmp->key))
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

char	*sub_value(char *str)
{
	int	i = 0;
	int s = 0;
	char *res;

	// if (str[i] == '"' || str[i])  here i have to handle qoutes like op="hello dsa";
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '=')
		{
			s = i + 1;
			if (!str[s])
				return (ft_strdup(""));
			res = handle_q(str, s);
			return (res);
		}
		i++;
	}
	return (NULL);
}


int	ft_export(char *s)
{
	int		i;
	int		exit;
	char	*key;
	char	*ss;
	char	*app;

	exit = 0;
	i = 0;
	i = skip(s);
	if (!(s[i]))
	{
		print_ex(neobash.envl);
		return (1);
	}
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i++;
		printf("entry is ::%s\n", &s[i]);
		if (parse_key(&s[i]))
		{
			ft_export_err_msg(&s[i]);
			return (1);
		}
		else
		{
			key = get_key(&s[i]);
			if (search_env(key))
			{
				printf("ok --> %s\n", key);
				if (neobash.app == true)
				{
					app = ft_strjoin(get_env_val(key), sub_value(&s[i]));
					update_env(key, app);
					printf("111key is ::%s |||| value is ::%s\n", key, app);
				}
				else
					update_env(key, sub_value(&s[i]));
			}
			else
			{
                ss = sub_value(&s[i]);
				exp_back(exp_new(key, ss));
			}
		}
		// printf("key is ::%s |||| value is ::%s\n", key, ss);
		i += neobash.count;
		// printf("ends in : %i \n", i);
		// free kay and ss here;
		// i have to incremenet here to get the new statmenet
	}
    return(exit);
}

// leaks in export;