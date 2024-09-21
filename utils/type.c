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


