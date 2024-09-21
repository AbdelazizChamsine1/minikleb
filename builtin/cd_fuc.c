/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_fuc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:03:12 by oismail           #+#    #+#             */
/*   Updated: 2024/09/03 16:11:59 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd1(void)
{
	char	*buff;
	char	*ptr;

	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
	{
		printf("memory allocation failed");
		return (NULL);
	}
	ptr = getcwd(buff, BUFF_SIZE);
	if (!ptr)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

int	env_add1(const char *key, const char *val, t_env **env)
{
	t_env	*new;
	t_env	*current;

	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(val);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (-1);
	}
	new->next = NULL;
	if (!env || !*env)
	{
		*env = new;
		return (SUCCESS);
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
	return (SUCCESS);
}

int	update_pwd(t_mini *mini)
{
	t_env	*current;
	char	*c;

	c = ft_pwd1();
	if (c == NULL)
		return (0);
	current = mini->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = c;
			return (1);
		}
		current = current->next;
	}
	free(c);
	return (0);
}

int	update_oldpwd(t_mini *mini)
{
	t_env	*current;
	char	*c;

	c = ft_pwd1();
	current = mini->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = c;
			return (1);
		}
		current = current->next;
	}
	env_add1("OLDPWD", c, &(mini->env));
	free(c);
	return (1);
}

int	cd_home(t_mini *mini)
{
	char	*home;

	if ((home = getenv("HOME")) == NULL)
	{
		perror("no valid path for home");
		return (1);
	}
	if (!update_oldpwd(mini))
	{
		perror("oldpwd");
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("error happened");
		return (-1);
	}
	if (!update_pwd(mini))
	{
		perror("failed to update PWD");
		return (-1);
	}
	return (0);
}
