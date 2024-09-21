#include "minishell.h"

// char	**cmd_tab(t_token *start)
// {
// 	t_token	*token;
// 	char	**tab;
// 	int		i;

// 	if (!start)
// 		return (NULL);
// 	token = start->next;
// 	i = 2;
// 	while (token)
// 	{
// 		token = token->next;
// 		i++;
// 	}
// 	if (!(tab = malloc(sizeof(char *) * i)))
// 		return (NULL);
// 	token = start->next;
// 	tab[0] = start->str;
// 	i = 1;
// 	while (token)
// 	{
// 		tab[i++] = token->str;
// 		token = token->next;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }

void expand_d(t_mini *mini, char **str)
{
    int i = 0;
    int j = 0;
    int len = strlen(*str);
    char *new_str = malloc(len + 10); // Allocate enough space for new string
    if (!new_str)
    {
        perror("Failed to allocate memory for new_str");
        exit(EXIT_FAILURE);
    }

    while ((*str)[i])
    {
        if ((*str)[i] == '$' && (*str)[i + 1] == '$')
        {
            j += sprintf(new_str + j, "%d", mini->pid);
            i += 2; // Skip over the `$$`
        }
        else
        {
            new_str[j++] = (*str)[i++];
        }
    }
    new_str[j] = '\0'; 

    free(*str);
    *str = new_str;
}


#include <unistd.h>

#define SUCCESS 0

int ft_echo(char **args) {
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n') {
        int j = 2;
        while (args[i][j] == 'n') {
            j++;
        }
        if (args[i][j] == '\0') {
            n_option = 1;
            i++;
        } else {
            break;
        }
    }
    while (args[i]) {
        int len = 0;
        while (args[i][len]) {
            len++;
        }
        write(1, args[i], len);
        if (args[i + 1]) {
            write(1, " ", 1);
        }        
        i++;
    }
    if (!n_option) {
        write(1, "\n", 1);
    }
    return (SUCCESS);
}
