/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:46:35 by achamsin          #+#    #+#             */
/*   Updated: 2024/08/27 13:56:43 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\')
	{
		if (line[i + 1] && (line[i + 1] == '|'
				|| line[i + 1] == '>'
				|| (line[i + 1] == '>' && line[i + 2] == '>')))
		{
			return (1);
		}
	}
	return (0);
}

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
	{
		(*i)++;
	}
}

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = TOKEN_EOF;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TOKEN_TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = TOKEN_APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = TOKEN_IN;
	else if (ft_strcmp(token->str, "<<") == 0 && separator == 0)
		token->type = TOKEN_HEREDOC;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = TOKEN_PIPE;
	else if (token->prev == NULL || token->prev->type >= TOKEN_TRUNC)
		token->type = TOKEN_WORD;
	else
		token->type = TOKEN_WORD;
}
