/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:31:18 by achamsin          #+#    #+#             */
/*   Updated: 2024/08/27 14:12:19 by achamsin         ###   ########.fr       */
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

void	handle_input(char *trimmed_input)
{
	char	*end;

	end = trimmed_input + strlen(trimmed_input) - 1;
	while (end > trimmed_input && *end == ' ')
		end--;
	end[1] = '\0';
	if (strcmp(trimmed_input, "exit") == 0)
		exit(0);
	if (strcmp(trimmed_input, "clear") == 0)
	{
		system("clear");
		return ;
	}
	if (!check_quotes(trimmed_input))
	{
		printf("Error: Unmatched quotes\n");
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
		display_tokens(tokens);
		while (tokens)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp->str);
			free(temp);
		}
	}
}

void	shell_loop(void)
{
	char	*input;
	int		i;
	char	*trimmed_input;

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
		handle_input(trimmed_input);
		process_command(input, trimmed_input);
		free(input);
	}
}
// void	shell_loop()
// {
// 	char	*input;
// 	t_token	*tokens;
// 	int		i;

// 	input = NULL;
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		input = readline("\033[0;92m\033[1mminishell ▸ \033[0m");
// 		if (!input) {
// 			printf("\n");
// 			break;
// 		}
// 		if (input[0] == '\0')
// 		{
// 			free(input);
// 			continue;
// 		}
// 		i = 0;
// 		ft_skip_space(input, &i);
// 		char *trimmed_input = input + i;
//         char *end = trimmed_input + strlen(trimmed_input) - 1;
//         while (end > trimmed_input && *end == ' ')
//             end--;
//         end[1] = '\0';
//         if (strcmp(trimmed_input, "exit") == 0) {
//             free(input);
//             break;
//         }
//         if (strcmp(trimmed_input, "clear") == 0) {
//             system("clear");
//             free(input);
//             continue;
//         }
//         add_history(input);
//         if (!check_quotes(input)) {
//             printf("Error: Unmatched quotes\n");
//             free(input);
//             continue;
//         }
//         tokens = get_tokens(trimmed_input);
//         display_tokens(tokens);
//         while (tokens) {
//             t_token *temp = tokens;
//             tokens = tokens->next;
//             free(temp->str);
//             free(temp);
//         }
//         free(input);
//     }
// }