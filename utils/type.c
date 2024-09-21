/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:06:43 by achamsin          #+#    #+#             */
/*   Updated: 2024/09/21 15:06:43 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int		has_type(t_token *token, int type)
{
	while (token)
	{
		if (is_type(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}

int		has_pipe(t_token *token)
{
	while (token && is_type(token, TOKEN_EOF) == 0)
	{
		if (is_type(token, TOKEN_PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

int	is_types(t_token *token, char *types)
{
	if (ft_strchr(types, 'P') && is_type(token, TOKEN_PIPE))
		return (1);
	else if (ft_strchr(types, 'T') && is_type(token, TOKEN_TRUNC))
		return (1);
	else if (ft_strchr(types, 'X') && is_type(token, TOKEN_CMD))
		return (1);
	else if (ft_strchr(types, 'x') && is_type(token, TOKEN_ARG))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(token, TOKEN_IN))
		return (1);
	else if (ft_strchr(types, 'H') && is_type(token, TOKEN_HEREDOC))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(token, TOKEN_APPEND))
		return (1);
	else if (ft_strchr(types, 'E') && is_type(token, TOKEN_EOF))
		return (1);
	else if (ft_strchr(types, ' ') && is_type(token, TOKEN_EMPTY))
		return (1);
	return (0);
}


