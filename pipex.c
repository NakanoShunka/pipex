/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/16 15:19:35 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_cmd1(t_pip	node, char **envp, char **argv)
{
	int		input_dup;
	int		outfile_dup;
	char	*path;
	int		exe;
	char	**split_line;


	input_dup = dup2(node.infile_fd, 0);
	if (input_dup == -1)
		exit(-1);
	outfile_dup = dup2(node.pipe_fd[1], 1);
	if (outfile_dup == -1)
		exit(-1);
	close(node.outfile_fd);
	close(node.pipe_fd[0]);
	split_line = ft_split(argv[2], ' ');
	if (!split_line)
		exit(-1);
	path = found_path(split_line[0], envp);
	if (!path)
		exit(-1);
	exe = execve(path, split_line, envp);
	if (exe == -1)
		exit (-1);
}

void	do_cmd2(t_pip	node, char **envp, char **argv)
{
	int		input_dup;
	int		outfile_dup;
	char	*path;
	int		exe;
	char	**split_line;

	input_dup = dup2(node.pipe_fd[0], 0);
	if (input_dup == -1)
		exit(-1);
	outfile_dup = dup2(node.outfile_fd, 1);
	if (outfile_dup == -1)
		exit(-1);
	close(node.infile_fd);
	close(node.pipe_fd[1]);
	split_line = ft_split(argv[3], ' ');
	if (!split_line)
		exit(-1);
	path = found_path(split_line[0], envp);
	if (!path)
		exit(-1);
	exe = execve(path, split_line, envp);
	if (exe == -1)
		exit (-1);
}

int	pipex_run(int argc, char **argv, char **envp)
{
	t_pip	node;
	int		result;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (-1);
	node.infile_fd = open(argv[1], O_RDONLY);
	if (node.infile_fd == -1)
		return (-1);
	node.outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node.outfile_fd == -1)
		return (-1);
	result = pipe(node.pipe_fd);
	if (result == -1)
		return (-1);
	pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (pid1 == 0)
	{
		do_cmd1(node, envp, argv);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		do_cmd2(node, envp, argv);
		exit(EXIT_FAILURE);
	}
	close(node.outfile_fd);
	close(node.pipe_fd[1]);
	close(node.infile_fd);
	close(node.pipe_fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}































