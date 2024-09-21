#include "minishell.h"

void	free_token(t_token *start)
{
    t_token *temp;

    while (start)
    {
        temp = start->next; // Save the next node
        ft_memdel(start->str); // Free the string in the current node
        ft_memdel(start); // Free the current node
        start = temp; // Move to the next node
    }
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			ft_memdel(tmp->key);
		if (tmp->value)
			ft_memdel(tmp->value);
		ft_memdel(tmp);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

