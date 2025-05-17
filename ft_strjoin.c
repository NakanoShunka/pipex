/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/15 22:08:44 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char	*str)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str)+ 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char s1[] = "42";
// 	printf("%s\n", ft_strdup(s1));
// }	

char	*ft_strjoin(char *s1, char	*s2)
{
	char		*result;
	size_t		i;
	size_t		j;
	size_t		all_len;

	if (!s1 || !s2)
		return (NULL);
	if (s2[0] == '\0')
		return (ft_strdup(s1));
	all_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(sizeof(char) * all_len);
	if (!result)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1) && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while ((i + j < all_len) && s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char *s1 = "42";
// 	char *s2 = "tokyo";
// 	printf("%s\n", ft_strjoin(s1, s2));
// }



