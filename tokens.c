#include "minishell.h"

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

static int		ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
				&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

static void	type_arg(t_token *token, int separator)
{
	if (strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

// void	squish_args(t_mini *mini)
// {
// 	t_token	*token;
// 	t_token	*prev;

// 	token = mini->start;
// 	while (token)
// 	{
// 		prev = prev_sep(token, NOSKIP);
// 		if (is_type(token, ARG) && is_types(prev, "TAI"))
// 		{
// 			while (is_last_valid_arg(prev) == 0)
// 				prev = prev->prev;
// 			token->prev->next = token->next;
// 			if (token->next)
// 				token->next->prev = token->prev;
// 			token->prev = prev;
// 			token->next = (prev) ? prev->next : mini->start;
// 			prev = (prev) ? prev : token;
// 			prev->next->prev = token;
// 			prev->next = (mini->start->prev) ? prev->next : token;
// 			mini->start = (mini->start->prev) ? mini->start->prev : mini->start;
// 		}
// 		token = token->next;
// 	}
// }

static int		next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

static t_token *create_special_token(char *line, int *i)
{
    t_token *token;
    int     j = 0;

    if (!(token = malloc(sizeof(t_token))))
        return (NULL);

    token->str = malloc(3 * sizeof(char));
    if (!token->str)
        return (NULL);

    token->str[j++] = line[(*i)++];
    if ((token->str[0] == '>' || token->str[0] == '<') && line[*i] == token->str[0])
        token->str[j++] = line[(*i)++];
    
    token->str[j] = '\0';
    return (token);
}

static t_token *create_regular_token(char *line, int *i)
{
    t_token *token;
    int     j = 0;
    char    c = ' ';

    if (!(token = malloc(sizeof(t_token))))
        return (NULL);
    
    if (!(token->str = malloc(sizeof(char) * next_alloc(line, i))))
        return (NULL);

    while (line[*i] && (line[*i] != ' ' || c != ' ') && !strchr("|;<>", line[*i])) {
        if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
            c = line[(*i)++];
        else if (c != ' ' && line[*i] == c) {
            c = ' ';
            (*i)++;
        } else if (line[*i] == '\\' && (*i)++)
            token->str[j++] = line[(*i)++];
        else
            token->str[j++] = line[(*i)++];
    }
    
    token->str[j] = '\0';
    return (token);
}

static t_token *next_token(char *line, int *i)
{
    if (strchr("|;<>", line[*i])) {
        return create_special_token(line, i);
    } else {
        return create_regular_token(line, i);
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
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}