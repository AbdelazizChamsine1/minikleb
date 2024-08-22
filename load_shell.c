#include "minishell.h"

void display_prompt() {
    write(STDERR_FILENO, "\033[0;92m\033[1mminishell ▸ \033[0m", 30);
}

// Signal handler for SIGINT
void handle_sigint(int sig) {
    (void)sig; // Suppress unused variable warning
    // Clear the line and redisplay the prompt
    write(STDERR_FILENO, "\n", 1);
    display_prompt();
}

void display_tokens(t_token *token) {
    while (token) {
        printf("%s\n", token->str);
        token = token->next;
    }
}

void shell_loop() {
    char *input = NULL;
    t_token *tokens;

    // Set up signal handling
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN); // Ignore SIGQUIT if you don't want to handle it

    while (1) {
        // display_prompt();
        input = readline("\033[0;92m\033[1mminishell ▸ \033[0m");  // Read input using readline
        if (!input) {
            // Handle end of file (Ctrl-D) or read error
            printf("\n");
            break;
        }

        if (input[0] == '\0') {
            // Empty input (press Enter without typing anything)
            free(input);
            continue;
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Add the input to history
        add_history(input);

        tokens = get_tokens(input);
        display_tokens(tokens); // Display each token on a new line

        // Free tokens after displaying them to avoid memory leaks
        while (tokens) {
            t_token *temp = tokens;
            tokens = tokens->next;
            free(temp->str);
            free(temp);
        }

        free(input); // Free the memory allocated by readline
    }
}
