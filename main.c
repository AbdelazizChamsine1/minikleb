// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/24 14:53:19 by oismail           #+#    #+#             */
// /*   Updated: 2024/09/21 12:12:13 by achamsin         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	free_env_list(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env;
// 		env = env->next;
		
// 		if (tmp->key)
// 			free(tmp->key);
// 		if (tmp->value)
// 			free(tmp->value);
		
// 		free(tmp);
// 	}
// }


// int main(int argc, char **argv, char **env)
// {
//     t_mini mini;

//     (void)argv;
//     if (argc != 1)
//     {
//         perror("only one argument");
//         exit(EXIT_FAILURE);
//     }
//     env_init(&mini, env);
//     secret_env_init(&mini, env);
//     increment_shell_level(mini.env);
//     shell_loop(&mini);
//     free_env_list(mini.env);
//     return (0);
// }
