/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:31:18 by achamsin          #+#    #+#             */
/*   Updated: 2024/09/12 12:53:43 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	check_quotes(const char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*input == '"' && single_quote == 0)
			double_quote = !double_quote;
		input++;
	}
	if (single_quote || double_quote)
		return (0);
	return (1);
}

void display_simple_tokens(t_simple *list) {
    t_simple *current = list;
    
    while (current) {
        printf("%s\n", current->str);
        current = current->next;
    }
}

void handle_input(char *input, t_mini *mini, char **args) {
    char *end;
    t_token *tokens = NULL;
    char **cmd_args;
    t_simple *cmds = NULL;  // This will store the commands separated by pipes

    if (!input || !args) {
        ft_putstr_fd("Error: Invalid input or arguments.\n", STDERR_FILENO);
        free(input);
        free_tab(args);
        return;
    }

    end = input + strlen(input) - 1;
    while (end > input && *end == ' ')
        end--;
    end[1] = '\0';

    tokens = get_tokens(input);

    cmd_args = cmd_tab(tokens);    
    mini->start = tokens;
    cmds = divide_pipe(mini);

    printf("Tokens from t_simple list:\n");
    display_simple_tokens(cmds);
    if (is_built(cmd_args)) {
        builtin_fuc(mini, cmd_args, input);
    } else if (strcmp(args[0], "clear") == 0) {
        system("clear");
        free_tab(cmd_args);
        return;
    } else {
        mini->ret = exec_bin(cmd_args, mini->env, mini);
        if (mini->ret == UNKNOWN_COMMAND) {
            ft_putstr_fd("Error: Command not found: ", STDERR_FILENO);
            ft_putstr_fd(cmd_args[0], STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
        }
    }
    t_simple *temp;
    while (cmds) {
        temp = cmds;
        cmds = cmds->next;
        free(temp->str);
        free(temp);
    }
}

void	process_command(char *input, char *trimmed_input)
{
	t_token	*tokens;
	t_token	*temp;

	add_history(input);
	if (check_quotes(trimmed_input))
	{
		tokens = get_tokens(trimmed_input);
		while (tokens)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp->str);
			free(temp);
		}
	}
}

void shell_loop(t_mini *mini)
{
    char *input;
    char *trimmed_input;
    char **args;

    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        input = readline("\033[0;92m\033[1mminishell ▸ \033[0m");
        if (!input)
        {
            ft_putstr_fd("\n", STDERR_FILENO);
            break;
        }
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        
        trimmed_input = ft_strtrim(input, " ");
        args = ft_split(trimmed_input, ' ');

        handle_input(trimmed_input, mini, args);

        free_tab(args);
    }
}
