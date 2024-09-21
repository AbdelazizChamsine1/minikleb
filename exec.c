#include "minishell.h"

void builtin_fuc(t_mini *mini, char **args, char *trimmed_input)
{
    t_token *tokens;
    char **expanded_args;
    int i;

    if (ft_strcmp(args[0], "exit") == 0)
    {
        free_tab(args);
        exit(0);
    }
    else if (ft_strcmp(args[0], "echo") == 0) {
        i = 0;
        while (args[i] != NULL) {
            if (ft_strchr(args[i], '$') != NULL) {
                expand_d(mini, &args[i]);
            }
            i++;
        }
        args = expander(mini, args);
        tokens = get_tokens(trimmed_input);
        expanded_args = cmd_tab(tokens);
        ft_echo(args);
        free_tab(expanded_args);
        free_tab(args);
        return;
    }
    else if (ft_strcmp(args[0], "env") == 0)
    {
        ft_env(mini->env);
        return ;
    }
    else if (ft_strcmp(args[0], "unset") == 0)
	{
		ft_unset(args, &mini->env);
        ft_unset(args, &mini->secret_env);
        return;
	}
    else if (ft_strcmp(args[0], "cd") == 0)
    {
		if (args[2])
		{
			printf("too many arguments\n");
			return ;
		}
        cd_file(mini, args[1]);
        return;
    }
    else if (ft_strcmp(args[0], "export") == 0)
    {
        ft_export(args, &mini->env, &mini->secret_env);
        return;
    }
    else if (ft_strcmp(args[0], "pwd") == 0)
    {
        ft_pwd();
        return;
    }
}

int is_built(char **args)
{
    if (ft_strcmp(args[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(args[0], "env") == 0)
        return (1);
    else if (ft_strcmp(args[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(args[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(args[0], "export") == 0)
        return (1);
    else if (ft_strcmp(args[0], "unset") == 0)
        return (1);
    else if (ft_strcmp(args[0], "exit") == 0)
        return (1);
    return (0);
}