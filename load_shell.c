#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_sigint(int sig) {
    (void)sig;
    write(STDERR_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int check_quotes(const char *input) {
    int single_quote = 0;
    int double_quote = 0;

    while (*input) {
        if (*input == '\'' && double_quote == 0)
            single_quote = !single_quote;
        else if (*input == '"' && single_quote == 0)
            double_quote = !double_quote;
        input++;
    }
    if (single_quote || double_quote) {
        return (0); 
    }
    return (1); 
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
        if (strcmp(trimmed_input, "clear") == 0) {
            system("clear");
            free(input);
            continue;
        }
        add_history(input);
        if (!check_quotes(input)) {
            printf("Error: Unmatched quotes\n");
            free(input);
            continue;
        }
        tokens = get_tokens(trimmed_input);
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

