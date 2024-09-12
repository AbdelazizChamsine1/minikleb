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

void handle_input(char *trimmed_input, t_mini *mini, char **args)
{
    char *end;
    t_token *tokens = NULL;
    char **cmd_args;

    if (!trimmed_input || !args)
    {
        printf("Error: Invalid input or arguments.\n");
        free(trimmed_input);
        free_tab(args);
        return;
    }

    end = trimmed_input + strlen(trimmed_input) - 1;
    while (end > trimmed_input && *end == ' ')
        end--;
    end[1] = '\0';
	
    if (ft_strcmp(args[0], "exit") == 0)
    {
        free(trimmed_input);
        free_tab(args);
        exit(0);
    }
	else if (strcmp(trimmed_input, "unset") == 0)
	{
		ft_unset(args, &mini->env);
	}
	else if (strcmp(trimmed_input, "env") == 0)
    {
        ft_env(mini->env);
        free_tab(args);
        return;
    }
    else if (ft_strcmp(args[0], "clear") == 0)
    {
        system("clear");
        free(trimmed_input);
        free_tab(args);
        return;
    }
    else if (ft_strcmp(args[0], "export") == 0)
    {
        ft_export(args, &mini->env, &mini->secret_env);
        free(args);
        return;
    }
    else if (ft_strcmp(args[0], "echo") == 0)
	{
    	int has_dollar = 0;
    	int i = 0;
    	while (args[i] != NULL)
    	{
        	if (ft_strchr(args[i], '$') != NULL)
        	{
            	has_dollar = 1;
            	break;
        	}
        	i++;
    	}
    	if (has_dollar)
	    {
        	cmd_args = expander(mini, args);
        	ft_echo(cmd_args);
        	free_tab(cmd_args);
    	}
    	else
    	{
        	tokens = get_tokens(trimmed_input);
        	cmd_args = cmd_tab(tokens);
        	ft_echo(cmd_args);
        	free_tab(cmd_args);
    	}	

    	return;
	}

    else if (ft_strcmp(args[0], "cd") == 0)
    {
		tokens = get_tokens(trimmed_input);
        cmd_args = cmd_tab(tokens);
		if (cmd_args[2])
		{
			printf("too many arguments\n");
			return ;
		}
        cd_file(mini, cmd_args[1]);
    }
	else 
    {
		tokens = get_tokens(trimmed_input);
        cmd_args = cmd_tab(tokens);
		
        if (!cmd_args || !cmd_args[0])
		{
			printf("error in cmd");
			return;
		}      
    	else
        	mini->ret = exec_bin(cmd_args, mini->env, mini);
    }
    
    free_tab(args);
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

void	shell_loop(t_mini *mini)
{
	char	*input;
	int		i;
	char	*trimmed_input;
	char 	**args;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("\033[0;92m\033[1mminishell ▸ \033[0m");
		if (!input)
		{
			printf("\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		i = 0;
		ft_skip_space(input, &i);
		trimmed_input = input + i;
		args = ft_split(trimmed_input, ' ');
		handle_input(trimmed_input, mini, args);
		process_command(input, trimmed_input);
		free(input);
	}
}
