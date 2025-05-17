/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2025/05/16 18:17:52 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h> 
#include <unistd.h>

typedef struct s_pip
{
	int	infile_fd;
	int	outfile_fd;
	int	pipe_fd[2];
}	t_pip;

typedef struct s_bpip
{
	int	infile_fd;
	int	outfile_fd;
	int	pipe_fd[2];
	int	**pip;
	int	pipe_count;
}	t_bpip;



char	*ft_strjoin(char *s1, char	*s2);
char	**ft_split(char *str, char c);
int		ft_strncmp(char	*s1, char *s2, size_t n);
int	pipex_run(int argc, char **argv, char **envp);
char	*found_path(char *cmd_name, char **envp);
void free_split(char **split_line);
void	do_cmd1(t_pip	node, char **envp, char **argv);
void	do_cmd2(t_pip	node, char **envp, char **argv);
int	bonus_pipex_run(int argc, char **argv, char **envp);
void	do_cmd3(t_bpip	node, char **envp, char **argv, int n, int argc);
void	ft_close_remove(t_bpip node, int	k, int j);

#endif