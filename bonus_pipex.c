/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/19 18:44:52 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	do_bcmd1(t_bpip	node, char **envp, char **argv)
{
	int		input_dup;
	int		outfile_dup;
	char	*path;
	int		exe;
	char	**split_line;


	input_dup = dup2(node.infile_fd, 0);
	if (input_dup == -1)
		exit(-1);
	close(node.infile_fd);
	outfile_dup = dup2(node.pip[0][1], 1);
	if (outfile_dup == -1)
		exit(-1);
	close(node.pip[0][1]);
	ft_close_remove(node, node.infile_fd, node.pip[0][1]);
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

void	do_bcmd2(t_bpip	node, char **envp, char **argv, int argc)
{
	int		input_dup;
	int		outfile_dup;
	char	*path;
	int		exe;
	char	**split_line;

	input_dup = dup2(node.pip[node.pipe_count - 1][0], 0);
	if (input_dup == -1)
		exit(-1);
	close(node.pip[node.pipe_count - 1][0]);
	outfile_dup = dup2(node.outfile_fd, 1);
	if (outfile_dup == -1)
		exit(-1);
	close(node.outfile_fd);
	ft_close_remove(node, node.pip[node.pipe_count - 1][0], node.outfile_fd);
	split_line = ft_split(argv[argc - 2], ' ');
	if (!split_line)
		exit(-1);
	path = found_path(split_line[0], envp);
	if (!path)
		exit(-1);
	exe = execve(path, split_line, envp);
	if (exe == -1)
		exit (-1);
}

void	ft_close(t_bpip node)
{
	int	i;


	close(node.outfile_fd);
	close(node.infile_fd);
	i = 0;
	while (i < node.pipe_count)
	{
		close(node.pip[i][0]);
		close(node.pip[i][1]);
		i++;
	}
	return ;
}

void	ft_close_remove(t_bpip node, int k, int j)
{
	int i = 0;
	while (i < node.pipe_count)
	{
		if (node.pip[i][0] != k && node.pip[i][0] != j) {
			fprintf(stderr, "close(fd=%d) @ %s:%d\n", node.pip[i][0], __FILE__, __LINE__);
			close(node.pip[i][0]);
		}
		if (node.pip[i][1] != k && node.pip[i][1] != j) {
			fprintf(stderr, "close(fd=%d) @ %s:%d\n", node.pip[i][1], __FILE__, __LINE__);
			close(node.pip[i][1]);
		}
		i++;
	}
	return ;
}


void	ft_waitpid(pid_t	*pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
}

void	do_cmd3(t_bpip	node, char **envp, char **argv, int n, int argc)
{
	int		input_dup;
	int		outfile_dup;
	char	*path;
	int		exe;
	char	**split_line;
	int		cmdc;

	cmdc = argc -3;
	if (n == 0 || n == cmdc -1)
		return ;
	input_dup = dup2(node.pip[n - 1][0], 0);
	if (input_dup == -1)
		exit(-1);
	close(node.pip[n - 1][0]);
	outfile_dup = dup2(node.pip[n][1], 1);
	if (outfile_dup == -1)
		exit(-1);
	close(node.pip[n][1]);
	close(node.outfile_fd);
	close(node.infile_fd);
	ft_close_remove(node, node.pip[n - 1][0], node.pip[n][1]);
	split_line = ft_split(argv[n + 2], ' ');
	if (!split_line)
		exit(-1);
	path = found_path(split_line[0], envp);
	if (!path)
		exit(-1);
	exe = execve(path, split_line, envp);
	if (exe == -1)
		exit (-1);
}

void	free_pipe_tab(int **pip, int n)
{
	int	i;
	
	i = 0;
	while (i < n)
	{
		free(pip[i]);
		i++;
	}
	free(pip);
}

int	bonus_pipex_run(int argc, char **argv, char **envp)
{
	int	cmdc;
	int	i;
	pid_t	*pid;
	t_bpip	node;
	int		result;

	if (argc < 5)
		return (0);
	cmdc = argc - 3;
	node.pipe_count = cmdc - 1;
	node.infile_fd = open(argv[1], O_RDONLY);
	if (node.infile_fd == -1)
		return (-1);
	node.outfile_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node.outfile_fd == -1)
		return (-1);
	node.pip = malloc(sizeof(int *) * (cmdc - 1));
	if (!node.pip)
		return (0);
	i = 0;
	while (i < node.pipe_count)
	{
		node.pip[i] = malloc(sizeof (int) * 2);
		if (!node.pip[i])
		{
			free_pipe_tab(node.pip, i);
			return (-1);
		}
		result = pipe(node.pip[i]);
		if (result == -1)
		{
			free_pipe_tab(node.pip, i + 1);
			return (-1);
		}
		i++;
	}
	pid = malloc (sizeof(pid_t) * (cmdc));
	if (!pid)
		return (0);
	i = 0;
	while (i < cmdc)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (0);
		if ((pid[i] == 0) && (i == 0))
		{
			do_bcmd1(node, envp, argv);
			exit(-1);
		}
		else if ((pid[i] == 0) && (i == cmdc - 1))
		{
			do_bcmd2(node, envp, argv, argc);
			exit(-1);
		}
		else if (pid[i] == 0)
		{
			do_cmd3(node, envp, argv, i, argc);
			exit(-1);
		}
		i++;
	}
	ft_close(node);
	ft_waitpid(pid);
	return (0);
}

