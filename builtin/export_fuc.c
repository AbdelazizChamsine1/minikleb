
#include "minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("bash : export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("bash : export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	env_add(const char *value, t_env **env)
{
    t_env	*new;
    t_env	*current;
    char	*key;
    char	*val;

    split_key_value(value, &key, &val);

    if (!env || !*env)
    {
        if (!(new = malloc(sizeof(t_env))))
            return (-1);
        new->key = key;
        new->value = val;
        new->next = NULL;
        *env = new;
        return (SUCCESS);
    }

    current = *env;
    if (current->value == NULL)
    {
        current->key = key;
        current->value = val;
        return (SUCCESS);
    }

    while (current->next)
        current = current->next;

    if (!(new = malloc(sizeof(t_env))))
        return (-1);

    new->key = key;
    new->value = val;
    new->next = NULL;
    current->next = new;

    return (SUCCESS);
}


char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_env **env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];
	char	*value;
	t_env	*current;

	get_env_name(var_name, args);
	value = ft_strchr(args, '=');
	if (value)
		value++;
	current = *env;
	while (current)
	{
		get_env_name(env_name, current->key);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(current->value);
			if (value)
				current->value = ft_strdup(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **env, t_env **secret)
{
	int		new_env;
	int		error_ret;
	int		i;

	if (!args[1])
	{
		ft_secret_env(*secret);
		return (SUCCESS);
	}
	i = 1;
	while (args[i])
	{
		error_ret = is_valid_env(args[i]);
		if (args[i][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
		{
			print_error(error_ret, args[i]);
			i++;
			continue ;
		}
		new_env = error_ret == 2 ? 1 : is_in_env(env, args[i]);
		if (new_env == 0)
		{
			if (error_ret == 1)
				env_add(args[i], env);
		}
		new_env = is_in_env(secret, args[i]);
		if (new_env == 0)
		{
			env_add(args[i], secret);
		}

		i++;
	}
	return (SUCCESS);
}
