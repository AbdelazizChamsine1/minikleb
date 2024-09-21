#include "minishell.h"

int check_append_outfile(t_token *redirection)
{
    int fd;

    if (redirection->type == TOKEN_APPEND)
        fd = open(redirection->str, O_CREAT | O_RDWR | O_APPEND, 0644);
    else if (redirection-> type == TOKEN_TRUNC)
        fd = open(redirection->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
    return fd;
}

int handle_infile(char *file)
{
    if (file == NULL)
    {
        ft_putstr_fd("minishell: infile: NULL file name\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }

    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: infile: No such file or directory\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }

    if (dup2(fd, STDIN_FILENO) < 0)
    {
        ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
        close(fd);
        return (EXIT_FAILURE);
    }
    close(fd);
    
    return (EXIT_SUCCESS);
}

int handle_outfile(t_token *redirection, int append)
{
    int fd;

    if (append)
        fd = open(redirection->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(redirection->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return EXIT_SUCCESS;
}


int check_redirections(t_mini *mini)
{
    t_token *current;

    if (!mini)
    {
        ft_putstr_fd("Error: mini is NULL\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }

    current = mini->start;
    while (current)
    {
        if (current->str == NULL)
        {
            ft_putstr_fd("Error: current->str is NULL. Skipping this token.\n", STDERR_FILENO);
            current = current->next;
            continue;
        }

        if (current->type == TOKEN_IN)
        {
            if (current->next == NULL || current->next->str == NULL)
            {
                ft_putstr_fd("Error: Missing file for input redirection\n", STDERR_FILENO);
                return (EXIT_FAILURE);
            }
            if (handle_infile(current->next->str))
            {
                ft_putstr_fd("Error: Failed to handle infile for: ", STDERR_FILENO);
                ft_putstr_fd(current->next->str, STDERR_FILENO);
                ft_putstr_fd("\n", STDERR_FILENO);
                return (EXIT_FAILURE);
            }
            current = current->next; // Skip the file name token
        }
        else if (current->type == TOKEN_OUT || current->type == TOKEN_APPEND)
        {
            if (current->next == NULL || current->next->str == NULL)
            {
                ft_putstr_fd("Error: Missing file for output redirection\n", STDERR_FILENO);
                return (EXIT_FAILURE);
            }
            if (handle_outfile(current->next, current->type == TOKEN_APPEND))
            {
                ft_putstr_fd("Error: Failed to handle outfile for: ", STDERR_FILENO);
                ft_putstr_fd(current->next->str, STDERR_FILENO);
                ft_putstr_fd("\n", STDERR_FILENO);
                return (EXIT_FAILURE);
            }
            current = current->next; // Skip the file name token
        }
        current = current->next;
    }

    return (EXIT_SUCCESS);
}
