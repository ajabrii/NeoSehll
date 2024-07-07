#include "../Header/headers.h"


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:16:20 by abelayad          #+#    #+#             */
/*   Updated: 2023/06/18 15:57:27 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static int	ft_export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	parse_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (1);
    i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_key(char *str)
{
	int	i;
	int s;

	s = 0;
	i = 0;
	if (str[i] == ' ')
		s = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, s, i - 1)); // for space before the key == hello( this )= ali
		i++;
	}
	return (ft_strdup(str));
}

bool search_env(char *s)
{
    t_env *env = neobash.envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

char	*sub_value(char *str)
{
	int	i = 0;
	int s = 0;
	neobash.count = 0;

	while (str[i])
	{
		if (str[i] == '=')
		{
			s = i + 1;
			while (str[s])
			{
				// printf("str[%i] = %c\n", s, str[s]);
				s++;
				if (!str[s] || str[s] == ' ')
				{
					neobash.count = s;
					return (ft_substr(str, i + 2, s - i - 1)); // + 1 for space after '='
				}
			}
		}
		i++;
	}
	printf("%i && %d\n", i, s);
	return (NULL);
}

int	ft_export(char *s)
{
	int		i;
    // char    **cmd;
	int		exit;
	char	*key;
	char	*ss;

	exit = 0;
	i = 0;
    // cmd = ft_split(s, ' ');

    // while (cmd[i])
    // {
    //     printf("cmd[%i] == %s\n", i, cmd[i]);
    //     i++;
    // }
    i = 7;
	// if (!s)
	// 	return (1);
	while (&s[i])
	{
		if (parse_key(&s[i]) == 0)
			exit = ft_export_err_msg(&s[i]);
		else
		{
			key = get_key(&s[i]);
			if (search_env(key))
			{
				// printf("kay is =%s\n", key);
				update_env(key, sub_value(&s[i]));
			}
			else
			{
                ss = sub_value(&s[i]);
				// printf("ss is =%s\n", ss);
				exp_back(exp_new(key, ss));
			}
		}
		i += neobash.count;
		// printf("ends in : %i \n", i);
		// free kay and ss here;
		printf("///////////////////////////////\n");
		if (!s[i] || !s[i + 1])
			return (exit);
		// i have to incremenet here to get the new statmenet
	}
	return (exit);
    return(0);
}
