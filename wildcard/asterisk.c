#include "../Header/headers.h"

int    match_pattern(const char *pattern, const char *filename)
{
    while (*pattern && *filename)
    {
        if (*pattern == '*')
        {
            if (*(pattern + 1) == '\0')
                return (1);
            while (*filename)
            {
                if (match_pattern(pattern + 1, filename++))
                    return (1);
            }
            return (0);
        }
        else if (*pattern != *filename)
            return (0);

        pattern++;
        filename++;
    }
    if (*pattern == *filename)
	    return (1);
    return (1);
}

    // return ((*pattern == '*' && *(pattern + 1) == '\0');

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
		if (entry->d_name[0] != '.' && match_pattern(s, entry->d_name))
		{
			res = ft_strjoin(res, " ");
			res = ft_strjoin(res, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (res);
}