/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/16 15:17:08 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*found_path(char *cmd_name, char **envp)
{
	char	**envp_split;
	int		i;
	int		j;
	char	*path;
	char	*full_path;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL); 
	envp_split = ft_split(envp[i] + 5, ':');
	if (!envp_split)
		return (NULL);
	j = 0;
	while (envp_split[j])
	{
		path = ft_strjoin(envp_split[j], "/");
		if (!path)
			return (free_split(envp_split), NULL);
		full_path = ft_strjoin(path, cmd_name);
		if (!full_path)
			return (free_split(envp_split), free(path), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_split(envp_split), free(path), full_path);
		free(path);
		free(full_path);
		j++;
	}
	return (free_split(envp_split), free(path), NULL);
}