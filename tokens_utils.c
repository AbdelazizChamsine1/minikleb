#include "minishell.h"

int ignore_sep(char *line, int i) {
    if (line[i] && line[i] == '\\') {
        if (line[i + 1] && (line[i + 1] == ';' || line[i + 1] == '|' || line[i + 1] == '>' || (line[i + 1] == '>' && line[i + 2] == '>'))) {
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
        token->type = EMPTY;
    } else if (strcmp(token->str, ">") == 0 && separator == 0) {
        token->type = TRUNC;
    } else if (strcmp(token->str, ">>") == 0 && separator == 0) {
        token->type = APPEND;
    } else if (strcmp(token->str, "<") == 0 && separator == 0) {
        token->type = INPUT;
    } else if (strcmp(token->str, "|") == 0 && separator == 0) {
        token->type = PIPE;
    } else if (strcmp(token->str, ";") == 0 && separator == 0) {
        token->type = END;
    } else if (token->prev == NULL || token->prev->type >= TRUNC) {
        token->type = CMD;
    } else {
        token->type = ARG;
    }
}