/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_fuc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:31:09 by oismail           #+#    #+#             */
/*   Updated: 2024/09/03 16:33:35 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buff;
	char	*ptr;

	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
	{
		printf("memory allocation failed");
		return ;
	}
	ptr = getcwd(buff, BUFF_SIZE);
	if (!ptr)
	{
		free(buff);
		return ;
	}
	write(1, buff, ft_strlen(buff));
	write(1, "\n", 1);
	free(buff);
}
