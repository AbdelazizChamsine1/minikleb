#include "minishell.h"

int redirect_out(t_mini *mini)
{
    t_token *current;
    int fd;

    fd = -1;
    current = mini->start;
    while (current != NULL)
    {
        if (current->type == TOKEN_TRUNC)
        {
            if (current->next == NULL || current->next->str == NULL)
            {
                ft_putstr_fd("bash: syntax error near unexpected token `newline`");
                return (-1);
            }
            fd = open(current->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (fd < 0)
            {
                ft_putstr_fd("bash: open");
                return (-1);
            }
        }
        else if (current->type == TOKEN_APPEND)
        {
            if (current->next == NULL || current->next->str == NULL)
            {
                ft_putstr_fd("bash: syntax error near unexpected token `newline`");
                return (-1);
            }
            fd = open(current->next->str, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (fd < 0)
            {
                ft_putstr_fd("bash: open");
                return (-1);
            }
            if (fd > 0 && dup2(fd, STDOUT_FILENO))
            {
                ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		        return (EXIT_FAILURE);
            }
            if (fd > 0)
                close(fd);
            return (0);
        }
        current = current->next;
    }
    return (fd); 
}

int redirect_in(t_mini)
{
    t_token *current;
    int fd;

    fd = -1;
    current = mini->start;
    while(current != NULL)
    {
        if (current->type == TOKEN_IN)
        {
            if (current->next->str == NULL)
            {
                ft_putstr_fd("bash: syntax error near unexpected token `newline`");
                return (-1);
            }
            fd = open(current->next->str, O_RDONLY, 644);
            if (fd < 0)
            {
                ft_putstr_fd("minishell: infile: No such file or directory",
			STDERR_FILENO);
                exit(EXIT_FAILURE);
            }
            if (fd > 0 && dup2(fd, STDIN_FILENO))
            {
		        ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		        return (EXIT_FAILURE);
	        }
            if (fd > 0)
                close(fd);
        }
    }
    return (fd);
}
