/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_fuc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:49 by oismail           #+#    #+#             */
/*   Updated: 2024/09/03 16:26:05 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delete_node(t_env **env, const char *value)
{
	t_env	*temp;
	t_env	*prev;
	char	key[BUFF_SIZE];
	int		deleted;

	deleted = 0;
	temp = *env;
	prev = NULL;
	get_env_name(key, value);
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (prev == NULL)
				*env = temp->next;
			else
				prev->next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			deleted = 1;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	return (deleted);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	deleted;

	i = 0;
	deleted = 0;
	while (args[i] != NULL)
	{
		if (delete_node(env, args[i]))
		{
			deleted = 1;
		}
		i++;
	}
	return (deleted);
}
