#include "../Header/headers.h"

int    matching_fun(char *pattern, char *name)
{
    while (*pattern && *name)
    {
        if (*pattern == '*')
        {
            if (*(pattern + 1) == '\0')
                return (1);
            while (*name)
            {
                if (matching_fun(pattern + 1, name++))
                    return (1);
            }
            return (0);
        }
        else if (*pattern != *name)
            return (0);
        pattern++;
        name++;
    }
	return (1);
}

char	*asterisk(char *s)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*res;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && matching_fun(s, entry->d_name))
		{
			res = ft_strjoin(res, " ");
			res = ft_strjoin(res, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (res);
}