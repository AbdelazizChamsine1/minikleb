/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:53:19 by oismail           #+#    #+#             */
/*   Updated: 2024/08/24 14:55:25 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_env *env)
{
    while (env)
    {
        printf("%s\n", env->value);
        env = env->next;
    }
}

int	main(int argc, char **argv, char **env)
{
	t_mini mini;

	(void)argv;
	if (argc != 1)
	{
		perror("only one argument");
		exit(EXIT_FAILURE);
	}
	env_init(&mini, env);
	secret_env_init(&mini, env);
	increment_shell_level(mini.env);
	print_env(mini.env);
	shell_loop();
	return (0);
}
