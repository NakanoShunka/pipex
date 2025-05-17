/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/16 15:20:33 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_split(char **split_line)
{
	int	i;
	
	i = 0;
	if (!split_line)
		return ;
	while(split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*res;

// 	if (argc < 0 || !argv)
// 		return (0);
// 	res = found_path("ls", envp);
// 	if (res)
// 	{
// 		printf("Found: %s\n", res);
// 		free(res);
// 	}
// 	else
// 		printf("Command not found\n");
// 	return (0);
// }