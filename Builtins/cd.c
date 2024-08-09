/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:58:07 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/09 12:23:17 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

int	update_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(cwd), 1);
	return (update_env("PWD", cwd), free(cwd),0);
}

int skip(char *s)
{
    int i = 0;

    while (s[i] && s[i] == ' ')
        i++;
    if (!s[i])
        return (0);
    return (i);
}
int count_args(char **s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

int bt_cd(char **s)
{
    // int i;
    // char *str;
    int c = 1;

    // i = skip(s[c]);
    if (count_args(s) > 2)
        return (ft_error("neobash: cd: too many arguments", NULL), 1);
    if (!s[c])
    {
        chdir("/home");
        update_env("OLDPWD", get_env_val("PWD"));
        // update_env("PWD", "/home");
        return (update_pwd(), 0);
    }
    // if (s[c][0] && s[c][0] == '~')
    // {
    //     c++;
    //     str = ft_strjoin("/home", s[c]);
    //     chdir(str);
    //     update_env("OLDPWD", get_env_val("PWD"));
    //     // update_env("PWD", str);
    //     free(str);
    //     return (update_pwd(), 0);
    // }
    else if(chdir(s[c]) == -1)
    {
        ft_error("cd", NULL);
        return(1);
    }
    update_env("OLDPWD", get_env_val("PWD"));
    return (update_pwd(), 0);
    // printf("%s\n", s);
}
