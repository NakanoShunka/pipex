/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/16 12:17:58 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	index_count(char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (-1);
	count = 0;
	if (str[0] != c)
		count++;
	i = 1;
	while (str[i])
	{
		if (str[i - 1] && (str[i] != c) && (str[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

// int	main(void)
// {
// 	char *str = "42 tokyo      happy     world    ";
// 	char c = ' ';
// 	printf("%d\n", index_count(str, c));
// 	return (0);
// }

char	**ft_split(char *str, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		index;
	int		start;
	int		end;
	int		len;

	if (!str)
		return (NULL);
	index = index_count(str, c);
	start = 0;
	end = 0;
	result = malloc(sizeof(char *) * (index + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] && (i < index))
	{
		while (str[j] && str[j] == c)
			j++;
		start = j;
		while (str[j] && str[j] != c)
			j++;
		end = j;
		len = end - start;
		result[i] = malloc(sizeof(char) * (len + 1));
		if (!result[i])
			return (NULL);
		k = 0;
		j = start;
		while ((k < len) && (j < end)) 
		{
			result[i][k] = str[j];
			j++;
			k++;
		}
		result[i][k] = '\0';
		i++;
	}
	result[i] = NULL;
	return (result);
}

// int	main(void)
// {
// 	char	**result;
// 	char	*str = "42 tokyo      happy     world    ";
// 	char c = ' ';
// 	int	i = 0;

// 	result = ft_split(str, c);
// 	while (result[i])
// 	{
// 		printf ("%s\n", result[i]);
// 		i++;
// 	}
// 	return (0);
// }


