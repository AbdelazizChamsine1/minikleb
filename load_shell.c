#include "minishell.h"

void display_prompt() {
    signal(SIGINT, SIG_IGN); 
    signal(SIGQUIT, SIG_IGN); 

    write(STDERR_FILENO, "\033[0;92m\033[1mminishell ▸ \033[0m", 30);
}

void display_tokens(t_token *token) {
    while (token) {
        printf("%s\n", token->str);
        token = token->next;
    }
}

void shell_loop() {
    char *input = NULL;
    size_t len = 0;

    while (1) {
        display_prompt();
        ssize_t nread = getline(&input, &len, stdin);
        if (nread == -1) {
            perror("getline");
            break;
        }
        if (nread > 1 && input[nread - 1] == '\n') {
            input[nread - 1] = '\0';
        }
        if (strcmp(input, "exit") == 0) {
            break;
        }

        t_token *tokens = get_tokens(input);
        display_tokens(tokens); // Display each token on a new line
        // Free tokens after displaying them to avoid memory leaks
        while (tokens) {
            t_token *temp = tokens;
            tokens = tokens->next;
            free(temp->str);
            free(temp);
        }
    }

    free(input);
}

