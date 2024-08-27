#include "minishell.h"

int ignore_sep(char *line, int i) {
    if (line[i] && line[i] == '\\') {
        if (line[i + 1] && (line[i + 1] == '|' || line[i + 1] == '>' || (line[i + 1] == '>' && line[i + 2] == '>'))) {
            return 1;
        }
    }
    return 0;
}

void ft_skip_space(const char *str, int *i) {
    while ((str[*i] == ' ' || str[*i] == '\t') ||
           (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f')) {
        (*i)++;
    }
}

void type_arg(t_token *token, int separator) {
    if (strcmp(token->str, "") == 0) {
        token->type = TOKEN_EOF;  // Or TOKEN_WORD if empty strings are considered words.
    } else if (strcmp(token->str, ">") == 0 && separator == 0) {
        token->type = TOKEN_TRUNC;
    } else if (strcmp(token->str, ">>") == 0 && separator == 0) {
        token->type = TOKEN_APPEND;
    } else if (strcmp(token->str, "<") == 0 && separator == 0) {
        token->type = TOKEN_IN;
    } else if (strcmp(token->str, "<<") == 0 && separator == 0) {
        token->type = TOKEN_HEREDOC;
    } else if (strcmp(token->str, "|") == 0 && separator == 0) {
        token->type = TOKEN_PIPE;
    } else if (token->prev == NULL || token->prev->type >= TOKEN_TRUNC) {
        token->type = TOKEN_WORD;  // Assuming TOKEN_WORD is used for commands
    } else {
        token->type = TOKEN_WORD;  // Arguments are also treated as words
    }
}