#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    while (1) {
        char* line = readline("Enter a command: ");
        if (!line) {
            break;
        }

        // Process the user input
        printf("You entered: %s\n", line);
        // Clear the current readline line
        rl_replace_line("", 0);

        // Move the cursor to a new line
        rl_on_new_line();

        // Redisplay the readline interface
        // rl_redisplay();
        // printf("\n");

        free(line);
    }

    return 0;
}