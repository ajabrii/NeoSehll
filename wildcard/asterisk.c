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
	char			*res = NULL;
    size_t i = 0;

    printf("ss is --->%s\n", s);
    while (s[i])
    {
        if (s[i] == '*')
        {
            while (s[i] != ' ' && i > 0)
                i--;
            break;
        }
        i++;
    }
    if (i == ft_strlen(s) || i <= 0)
        return (s);
    res = ft_substr(s, 0, i);
    i++;
    printf("here\n");
    printf("ss after is --->%s && i = %zu\n", res, i);
    dir = opendir(".");
    if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(&s[i], entry->d_name))
		{
			res = ft_strjoin(res, " ");
			res = ft_strjoin(res, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
    printf("----%s----\n", res);
    return (res);
}
// i still have to split args if i have like :"ls -l t*.c c*.c";
// algo fails when i do "touch test*.c";
// problem in cd folder;
