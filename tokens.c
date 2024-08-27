/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:40:13 by oismail           #+#    #+#             */
/*   Updated: 2024/08/27 14:11:43 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

const char	*get_token_type_name(t_tokens type) {
	switch (type) {
		case TOKEN_PIPE: return "PIPE";
		case TOKEN_TRUNC: return "TRUNC";
		case TOKEN_WORD: return "WORD";
		case TOKEN_IN: return "IN";
		case TOKEN_OUT: return "OUT";
		case TOKEN_HEREDOC: return "HEREDOC";
        case TOKEN_APPEND: return "APPEND";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
	}
}

void	display_tokens(t_token *token) {
	while (token) {
		printf("Token: '%s', Type: %s\n", token->str, get_token_type_name(token->type));
		token = token->next;
	}
}

static int	next_alloc(char *line, int *i)
{
	int     count;
	int     j;
	char    c;

    count = 0;
    j = 0;
    c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
		{
			c = line[*i + j++];
		}
		else if (c != ' ' && line[*i + j] == c)
		{
			j++;
			break ;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

static	t_token	*create_special_token(char *line, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(t_token));
	if (!token)
	{
		return (NULL);
	}
	token->str = malloc(3 * sizeof(char));
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->str[j++] = line[(*i)++];
	if ((token->str[0] == '>'
		|| token->str[0] == '<') && line[*i] == token->str[0])
	{
		token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

static	t_token	*create_regular_token(char *line, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	while (line[*i] && !strchr("|<>", line[*i]) && line[*i] != ' ')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			if (j > 0)
			{
				token->str[j] = '\0';
				return (token);
			}
			(*i)++;
			while (line[*i] && line[*i] != '\'' && line[*i] != '\"')
				token->str[j++] = line[(*i)++];
			if (line[*i])
			{
				(*i)++; 
			}
			token->str[j] = '\0';
			return (token);
		}
		else if (line[*i] == '\\' && line[*i + 1])
		{
			token->str[j++] = line[++(*i)];
		}
		else
		{
			token->str[j++] = line[(*i)++];
		}
	}
	token->str[j] = '\0';
	if (j == 0)
	{
		free(token->str);
		free(token);
		return (NULL);
	}
	return (token);
}

static	t_token	*next_token(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
	if (strchr("|<>", line[*i]))
	{
		return (create_special_token(line, i));
	}
	else
	{
		return (create_regular_token(line, i));
	}
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		if (!next)
			continue ;
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
