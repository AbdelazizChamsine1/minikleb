#include "minishell.h"
#include <stdio.h> // For debugging purposes

static int next_alloc(char *line, int *i) {
    int count = 0;
    int j = 0;
    char c = ' ';

    while (line[*i + j] && (line[*i + j] != ' ' || c != ' ')) {
        if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"')) {
            c = line[*i + j++];
        } else if (c != ' ' && line[*i + j] == c) {
            j++;  // Move past the closing quote
            break;  // Stop counting at the end of the quoted string
        } else {
            j++;
        }
        if (line[*i + j - 1] == '\\') {
            count--;
        }
    }
    return (j - count + 1);
}

static t_token *create_special_token(char *line, int *i) {
    t_token *token;
    int j = 0;
    if (!(token = malloc(sizeof(t_token)))) {
        return NULL;
    }
    token->str = malloc(3 * sizeof(char));
    if (!token->str) {
        free(token);
        return NULL;
    }
    token->str[j++] = line[(*i)++];
    if ((token->str[0] == '>' || token->str[0] == '<') && line[*i] == token->str[0]) {
        token->str[j++] = line[(*i)++];
    }
    token->str[j] = '\0';
    return token;
}

static t_token *create_regular_token(char *line, int *i) {
    t_token *token;
    int j = 0;

    if (!(token = malloc(sizeof(t_token)))) {
        return NULL;
    }
    if (!(token->str = malloc(sizeof(char) * next_alloc(line, i)))) {
        free(token);
        return NULL;
    }

    while (line[*i] && !strchr("|;<>", line[*i]) && line[*i] != ' ') {
        if (line[*i] == '\'' || line[*i] == '\"') {
            if (j > 0) {
                token->str[j] = '\0';
                return token;
            }
            (*i)++;
            while (line[*i] && line[*i] != '\'' && line[*i] != '\"') {
                token->str[j++] = line[(*i)++];
            }
            if (line[*i]) {
                (*i)++; 
            }
            token->str[j] = '\0';
            return token;
        } else if (line[*i] == '\\' && line[*i + 1]) {
            token->str[j++] = line[++(*i)];
        } else {
            token->str[j++] = line[(*i)++];
        }
    }
    token->str[j] = '\0';
    if (j == 0) {
        free(token->str);
        free(token);
        return NULL;
    }
    return token;
}


static t_token *next_token(char *line, int *i) {
    while (line[*i] == ' ') {
        (*i)++;
    }

    if (strchr("|;<>", line[*i])) {
        return create_special_token(line, i);
    } else {
        return create_regular_token(line, i);
    }
}

t_token *get_tokens(char *line) {
    t_token *prev = NULL;
    t_token *next = NULL;
    int i = 0;
    int sep;

    while (line[i]) {
        sep = ignore_sep(line, i);
        next = next_token(line, &i);

        if (!next) {
            continue;
        }

        next->prev = prev;
        if (prev) {
            prev->next = next;
        }
        prev = next;
        type_arg(next, sep);
    }

    if (next) {
        next->next = NULL;
    }
    while (next && next->prev) {
        next = next->prev;
    }
    return next;
}
