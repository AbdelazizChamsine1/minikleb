/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_secret.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:04 by oismail           #+#    #+#             */
/*   Updated: 2024/09/06 18:07:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	secret_env_init(t_mini *mini, char **env_array)
// {
// 	t_env	*env;
// 	t_env	*new;
// 	int		i;

// 	env = malloc(sizeof(t_env));
// 	if (!env)
// 		return (1);
// 	env->value = ft_strdup(env_array[0]);
// 	env->next = NULL;
// 	mini->secret_env = env;
// 	i = 1;
// 	while (env_array && env_array[0] && env_array[i])
// 	{
// 		new = malloc(sizeof(t_env));
// 		if (!new)
// 			return (1);
// 		new->value = ft_strdup(env_array[i]);
// 		new->next = NULL;
// 		env->next = new;
// 		env = new;
// 		i++;
// 	}
// 	return (0);
// }

int secret_env_init(t_mini *mini, char **env_array)
{
    t_env *env;
    t_env *new;
    int i;

    if (!env_array || !env_array[0])
        return (1);
    env = malloc(sizeof(t_env));
    if (!env)
        return (1);

    char *key;
    char *value;
    split_key_value(env_array[0], &key, &value);
    env->key = key;
    env->value = value;
    env->hidden = 0;
    env->next = NULL;
    mini->secret_env = env;
    i = 1;
    while (env_array[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return (1);

        split_key_value(env_array[i], &key, &value);
        new->key = key;
        new->value = value;
        new->hidden = 0;
        new->next = NULL;
        env->next = new;
        env = new;
        i++;
    }
    return (0);
}