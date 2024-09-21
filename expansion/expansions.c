/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:49:03 by achamsin          #+#    #+#             */
/*   Updated: 2024/09/12 12:49:03 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

int	loop_if_dollar_sign(t_mini *mini, char *str, char **tmp, int j)
{
	int		ret;
	char	*tmp2;
	char	*tmp3;
	t_env	*env_node;

	ret = 0;
	env_node = mini->env;
	while (env_node)
	{
		if (ft_strncmp(str + j + 1, env_node->key, ft_strlen(env_node->key)) == 0)
		{
			tmp2 = ft_strdup(env_node->value);
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(env_node->key);
		}
		env_node = env_node->next;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

int	handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]))
		{
			j += 2;
		}
	}
	return (j - i);
}

char	*detect_dollar_sign(t_mini *mini, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(mini, &tmp);
		if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
				|| str[j + 2] != '\0')) && str[j + 1] != '\0')
				{
					j += loop_if_dollar_sign(mini, str, &tmp, j);
				}
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

char	**expander(t_mini *mini, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (str[i][dollar_sign(str[i]) - 2] != '\'' && dollar_sign(str[i]) != 0
			&& str[i][dollar_sign(str[i])] != '\0')
		{
			tmp = detect_dollar_sign(mini, str[i]);
			free(str[i]);
			str[i] = tmp;
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
		{
			str[i] = delete_quotes(str[i], '\"');
			str[i] = delete_quotes(str[i], '\'');
		}
		i++;
	}
	return (str);
}

bool	is_escaped(const char *str, int index)
{
	int	backslash_count;

	backslash_count = 0;
	while (index >= 0 && str[index] == '\\')
	{
		backslash_count++;
		index--;
	}
	return (backslash_count % 2 != 0);
}

char	*handle_mixed_quotes(const char *str)
{
	size_t	len;
	char	*result;
	char	outer_quote;

	len = ft_strlen(str);
	if (len < 2)
		return (strdup(str));
	outer_quote = '\0';
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len - 1] == '\"'))
		outer_quote = str[0];
	if (outer_quote)
	{
		result = malloc(len - 1);
		if (!result) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strncpy(result, str + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (strdup(str));
}

char	*expander_str(t_mini *mini, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[dollar_sign(str) - 2] != '\'' && dollar_sign(str) != 0
		&& str[dollar_sign(str)] != '\0')
	{
		tmp = detect_dollar_sign(mini, str);
		free(str);
		str = tmp;
	}
	str = delete_quotes(str, '\"');
	str = delete_quotes(str, '\'');
	return (str);
}

