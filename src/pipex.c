/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tylerlover911 <tylerlover911@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:00:02 by tylerlover9       #+#    #+#             */
/*   Updated: 2025/03/28 23:06:58 by tylerlover9      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec(char *command, char **env, int fd_pid[2])
{
	char	*path;
	char	**cmd_split;

	cmd_split = ft_split(command, ' ');
	path = set_path(cmd_split[0], env);
	if (execve(path, cmd_split, env) == -1)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(command, 2);
		free(path);
		ft_freetab(cmd_split);
		close(fd_pid[0]);
		close(fd_pid[1]);
		exit(127);
	}
}

void	parent(char **av, int fd_pid[2], char **env)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit(1);
	dup2(fd, 1);
	dup2(fd_pid[0], 0);
	close(fd_pid[1]);
	exec(av[3], env);
}

void	kid(char **av, int fd_pid[2], char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
		exit(1);
	}
	dup2(fd, 0);
	dup2(fd_pid[1], 1);
	close(fd_pid[0]);
	exec(av[2], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd_pid[2];
	pid_t	pid;

	if (ac != 5)
		return (0);
	if (pipe(fd_pid) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (!pid)
		kid(av, fd_pid, env);
	parent(av, fd_pid, env);
}
