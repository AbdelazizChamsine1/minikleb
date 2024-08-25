/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:53:19 by oismail           #+#    #+#             */
/*   Updated: 2024/08/24 14:55:25 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		perror("only one argument");
		exit(EXIT_FAILURE);
	}
	shell_loop();
	return (0);
}
