#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
# include "./Header/headers.h"

char *handle_q(char *line)
{
    char *res;
    int i;
    int start;
    char q;
    int nargs;

    i = 0;
    res = malloc(sizeof(char) * (ft_strlen(line) + 1));
    if (!res)
        return NULL;

        while (line[i] && line[i] == ' ') // don't forget to change this to libft functio ft_isspace !!!
            i++;
        if (line[i] == '\0')
		{
			res[i] = '\0';
            return (res);
		}
        if (line[i] == '\"' || line[i] == '\'')
        {
            q = line[i];
            i++;
            start = i;
            while (line[i] && line[i] != q)
                i++;
            if (line[i] == q)
                i++;
            res = ft_substr(line, start, i - start - 1);
        }
        else
        {
            start = i;
            while (line[i] && line[i] != ' ')
                i++;
            res = ft_substr(line, start, i - start);
        }
    res[i] = '\0';
    return res;
}

int main()
{
    char *ss;

    ss = handle_q("hello wolrd");
    printf("%s\n", ss);
}
