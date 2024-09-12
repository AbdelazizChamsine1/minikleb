

#include "minishell.h"

void	handle_pipe_execution(t_mini *mini, t_token *token)
{
    int pipe_fd[2];
    pid_t pid;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == 0)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exec_cmd(mini, token);
    }
    else
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);

        t_token *next_command = next_type(token, TOKEN_PIPE, 1);
        if (next_command)
        {
            exec_cmd(mini, next_command);
        }
    }
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

    if (mini->charge == 0)
        return ;
    cmd = cmd_tab(token);
    i = 0;
    while (cmd && cmd[i])
    {
        cmd[i] = expansions(cmd[i], mini->env, mini->ret);
        i++;
    }
    if (has_pipe(token))
        handle_pipe_execution(mini, token);
    else if (cmd && ft_strcmp(cmd[0], "exit") == 0)
        mini_exit(mini, cmd);
    else if (cmd && is_builtin(cmd[0]))
        mini->ret = exec_builtin(cmd, mini);
    else if (cmd)
        mini->ret = exec_bin(cmd, mini->env, mini);
    free_tab(cmd);
    ft_close(mini->pipin);
    ft_close(mini->pipout);
    mini->pipin = -1;
    mini->pipout = -1;
    mini->charge = 0;
}
