#include "minishell.h"

void display_prompt() {
    write(STDERR_FILENO, "\033[0;92m\033[1mminishell ▸ \033[0m", 30);
}

void handle_sigint(int sig) {
    (void)sig; 
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
    int i;

    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    while (1) {
        input = readline("\033[0;92m\033[1mminishell ▸ \033[0m");
        if (!input) {
            printf("\n");
            break;
        }
        if (input[0] == '\0') {
            free(input);
            continue;
        }
        i = 0;
        ft_skip_space(input, &i);
        char *trimmed_input = input + i;
        char *end = trimmed_input + strlen(trimmed_input) - 1;
        while (end > trimmed_input && *end == ' ')
            end--;
        end[1] = '\0';

        if (strcmp(trimmed_input, "exit") == 0) {
            free(input);
            break;
        }
        add_history(input);
        tokens = get_tokens(input);
        display_tokens(tokens);
        while (tokens) {
            t_token *temp = tokens;
            tokens = tokens->next;
            free(temp->str);
            free(temp);
        }
        free(input);
    }
}
