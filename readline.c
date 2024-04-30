#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;
	while(1)
	{
    	line = readline("Prompt > ");
    	printf("%s\n", line);
	}
    return (0);
}