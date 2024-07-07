# include "../Header/headers.h"


char	*get_env_val(char *key)
{
	t_env	*envlst;

	envlst = neobash.envl;
	while (envlst)
	{
		if (!ft_strncmp(key, envlst->key, ft_strlen(key)))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	update_env(char *key, char *value)
{
	t_env	*envlst;

	envlst = neobash.envl;
	while (envlst)
	{
		if (!ft_strncmp(key, envlst->key, ft_strlen(key)))
		{
			if (value)
				envlst->value = ft_strdup(value);
			return ;
		}
		envlst = envlst->next;
	}
}
