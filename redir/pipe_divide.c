#include "minishell.h"


int is_type1(t_token *token, int type) {
    return (token && token->type == type);
}

t_simple *create_simple_node(const char *str) {
    t_simple *node = (t_simple *)malloc(sizeof(t_simple));
    if (!node) return NULL;
    node->str = strdup(str); 
    node->next = NULL;
    return node;
}
void append_simple_node(t_simple **head, const char *str) {
    t_simple *new_node = create_simple_node(str);
    if (!new_node) return;
    
    if (!*head) {
        *head = new_node;
    } else {
        t_simple *temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
t_simple *divide_pipe(t_mini *mini) {
    t_token *current;
    t_simple *head = NULL;
    char *command = NULL;
    size_t command_size = 0;
    
    if (!mini || !mini->start) {
        return NULL;
    }

    current = mini->start;
    while (current) {
        if (is_type1(current, TOKEN_PIPE)) {
            if (command) {
                append_simple_node(&head, command);
                free(command);
                command = NULL;
                command_size = 0;
            }
        } else {
            size_t token_len = strlen(current->str);
            command = (char *)realloc(command, command_size + token_len + 2);
            if (!command) return NULL;
            if (command_size > 0) {
                command[command_size] = ' ';
                command_size++;
            }
            memcpy(command + command_size, current->str, token_len);
            command_size += token_len;
            command[command_size] = '\0';
        }
        current = current->next;
    }
    
    if (command) {
        append_simple_node(&head, command);
        free(command);
    }

    return head;
}
