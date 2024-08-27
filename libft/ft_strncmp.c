/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamsin <achamsin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:47:05 by achamsin          #+#    #+#             */
/*   Updated: 2024/06/12 17:45:46 by achamsin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
//#include<stdio.h>

// int	ft_strncmp(char *s1, char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
// 	{
// 		if (s1[i] > s2[i])
// 		{
// 			return (1);
// 		}
// 		else if (s1[i] < s2[i])
// 		{
// 			return (-1);
// 		}
// 		i++ ;
// 	}
// 	return (0);
// }

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

//int main(void)
//{
//	printf("%d", ft_strncmp("aCCD", "cAAd", 2));
//	return (0);
//}
