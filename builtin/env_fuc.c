/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fuc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:19:05 by oismail           #+#    #+#             */
/*   Updated: 2024/09/12 12:36:19 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->value && env->value[0] != '\0')
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (SUCCESS);
}


int	ft_secret_env(t_env *env)
{
	while (env)
	{
		if (env->key)
			printf("declare -x %s=", env->key);
		if (env->value)
			printf("%s\n", env->value);
		env = env->next;
	}
	return (SUCCESS);
}