/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:31:18 by achamsin          #+#    #+#             */
/*   Updated: 2024/09/12 12:35:42 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_file(t_mini *mini, char *path)
{
	if ( !check_quotes(path))
	{
		printf("Error syntax quotes\n");
		return (-1);
	}
	delete_quotes(path, '\'');
	delete_quotes(path, '\"');
	if (!update_oldpwd(mini))
	{
		perror("oldpwd cannot be updated");
		return (-1);
	}
	if (chdir(path) != 0)
	{
		printf("cd : No such file or directory : %s\n", path);
		return (-1);
	}
	if (! update_pwd(mini))
	{
		perror("failed to update the pwd");
		return (-1);
	}
	return (0);
}

int	cd_last(t_mini *mini)
{
	char	*old;
	char	*dir;
	t_env	*current;

	old = ft_pwd1();
	if (!old)
		return (1);
	dir = strrchr(old, '/');
	if (dir != NULL)
	{
		if (dir == old)
		{
			free(old);
			return (1);
		}
		*dir = '\0';
		update_oldpwd(mini);
		if (chdir(old) != 0)
		{
			free(old);
			return (1);
		}
		current = mini->env;
		while (current != NULL)
		{
			if (ft_strcmp(current->key, "PWD") == 0)
			{
				char *new_value = strdup(old);
				if (new_value == NULL) {
					free(old);
					return (1);
				}
				free(current->value);
				current->value = new_value;
				break ;
			}
			current = current->next;
		}
		free(old);
	}
	else
	{
		free(old);
		return (1);
	}
	return (0);
}

int	cd_dash(t_mini *mini)
{
	char	*arg;
	t_env	*current;

	current = mini->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			arg = current->value;
			if (arg == NULL)
			{
				printf("bash : cd : OLDPWD not set");
				return (1);
			}
			printf("%s\n", arg);
			if (chdir(arg) != 0)
				return (1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
