/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tylerlover911 <tylerlover911@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:00:02 by tylerlover9       #+#    #+#             */
/*   Updated: 2025/03/24 20:13:05 by tylerlover9      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parent(char **av, int fd_pid[2], char **env)
{
	int	fd;
	
	fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit (0);
	dup2(fd, 1);
	dup2(fd_pid[0], 0);
	close(fd_pid[1]);
}

void	kid(char **av, int fd_pid[2], char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(0);
	dup2(fd, 0);
	dup2(fd_pid[0], 1);
	close(fd_pid[1]);
}

int main(int ac, char **av, char **env)
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
