#include "minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token)
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

// static	int	nb_args(char **args)
// {
// 	int		size;

// 	size = 0;
// 	while (args[size])
// 		size++;
// 	return (size);
// }

// int	ft_echo(char **args)
// {
// 	int		i;
// 	int		n_option;

// 	i = 1;
// 	n_option = 0;
// 	if (nb_args(args) > 1)
// 	{
// 		while (args[i] && ft_strcmp(args[i], "-n") == 0)
// 		{
// 			n_option = 1;
// 			i++;
// 		}
// 		while (args[i])
// 		{
// 			ft_putstr_fd(args[i], 1);
// 			if (args[i + 1] && args[i][0] != '\0')
// 				write(1, " ", 1);
// 			i++;
// 		}
// 	}
// 	if (n_option == 0)
// 		write(1, "\n", 1);
// 	return (SUCCESS);
// }

int	ft_echo(char **args)
{
	int	i;
	int	j;
	int	n_option;

	i = 1;
	n_option = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			n_option = 1;
			i++;
		}
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	return (SUCCESS);
}
