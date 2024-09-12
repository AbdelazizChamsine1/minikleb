/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:46:21 by achamsin          #+#    #+#             */
/*   Updated: 2024/09/12 13:15:55 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst)
	{
		if (lst->value != NULL && !lst->hidden)
		{
			lst_len += strlen(lst->key);
			lst_len += 1;
			lst_len += strlen(lst->value);
			lst_len += 1;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;
	int		total_size;

	total_size = size_env(lst) + 1;
	env = malloc(sizeof(char) * total_size);
	if (!env)
		return (NULL);

	i = 0;
	while (lst != NULL)
	{
		if (lst->value != NULL && !lst->hidden)
		{
			j = 0;
			while (lst->key[j])
				env[i++] = lst->key[j++];
			env[i++] = '=';
			j = 0;
			while (lst->value[j])
				env[i++] = lst->value[j++];
			if (lst->next != NULL && lst->next->value != NULL && !lst->next->hidden)
				env[i++] = '\n';
		}
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

void	split_key_value(const char *env_str, char **key, char **value)
{
	const char	*equal_sign;
	size_t		key_len;

	equal_sign = strchr(env_str, '=');
	if (equal_sign)
	{
		key_len = equal_sign - env_str;
		*key = (char *)malloc(key_len + 1);
		*value = strdup(equal_sign + 1);
		if (*key)
		{
			strncpy(*key, env_str, key_len);
			(*key)[key_len] = '\0';
		}
	}
	else
	{
		*key = strdup(env_str);
		*value = strdup("");
	}
}


int	env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	split_key_value(env_array[0], &env->key, &env->value);
	env->hidden = 0;
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		split_key_value(env_array[i], &new->key, &new->value);
		new->hidden = 0;
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
