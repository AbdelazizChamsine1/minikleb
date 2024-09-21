/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_secret.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:04 by oismail           #+#    #+#             */
/*   Updated: 2024/09/21 10:34:08 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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