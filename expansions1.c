#include "minishell.h"

int	question_mark(t_mini *mini, char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(mini->error_num);
	return (ft_strlen(*tmp) + 1);
}

size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}