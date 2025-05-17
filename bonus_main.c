/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/16 16:25:38 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int argc, char **argv, char **envp)
// {

// 	if (argc < 0)
// 		return (-1);
// 	bonus_pipex_run(argc, argv, envp);
// 		exit (-1);
// 	return (0);
// }

#include <unistd.h>
#include <string.h>
#include "pipex.h"

void write_debug(const char *msg)
{
	write(2, msg, strlen(msg));
}

int main(int argc, char **argv, char **envp)
{
	int fd = open("debug.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dprintf(fd, "STARTED pipex\n");
	write_debug("=== PIPEX DEBUG START ===\n");

	for (int i = 0; argv[i]; i++)
	{
		write_debug("argv[");
		char num[10];
		int len = snprintf(num, sizeof(num), "%d", i);
		write(2, num, len);
		write_debug("] = ");
		write(2, argv[i], strlen(argv[i]));
		write_debug("\n");
	}

	write_debug("=== PIPEX DEBUG END ===\n");

	if (argc < 5)
	{
		write_debug("Error: not enough arguments\n");
		return (1);
	}
	return (bonus_pipex_run(argc, argv, envp));
}
