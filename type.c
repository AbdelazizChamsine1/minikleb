#include "minishell.h"

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

// int		is_types(t_token *token, char *types)
// {
// 	if (ft_strchr(types, ' ') && is_type(token, EMPTY))
// 		return (1);
// 	else if (ft_strchr(types, 'X') && is_type(token, CMD))
// 		return (1);
// 	else if (ft_strchr(types, 'x') && is_type(token, ARG))
// 		return (1);
// 	else if (ft_strchr(types, 'T') && is_type(token, TRUNC))
// 		return (1);
// 	else if (ft_strchr(types, 'A') && is_type(token, APPEND))
// 		return (1);
// 	else if (ft_strchr(types, 'I') && is_type(token, INPUT))
// 		return (1);
// 	else if (ft_strchr(types, 'P') && is_type(token, PIPE))
// 		return (1);
// 	else if (ft_strchr(types, 'E') && is_type(token, END))
// 		return (1);
// 	return (0);
// }

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

int	is_types(t_token *token, char *types)
{
	if (ft_strchr(types, '|') && is_type(token, TOKEN_PIPE))
		return (1);
	else if (ft_strchr(types, '>') && is_type(token, TOKEN_TRUNC))
		return (1);
	else if (ft_strchr(types, 'w') && is_type(token, TOKEN_WORD))
		return (1);
	else if (ft_strchr(types, '<') && is_type(token, TOKEN_IN))
		return (1);
	else if (ft_strchr(types, 'o') && is_type(token, TOKEN_OUT))
		return (1);
	else if (ft_strchr(types, 'h') && is_type(token, TOKEN_HEREDOC))
		return (1);
	else if (ft_strchr(types, 'a') && is_type(token, TOKEN_APPEND))
		return (1);
	else if (ft_strchr(types, 'e') && is_type(token, TOKEN_EOF))
		return (1);
	return (0);
}

int	has_pipe(t_token *token)
{
	while (token && is_type(token, TOKEN_EOF) == 0)
	{
		if (is_type(token, TOKEN_PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
