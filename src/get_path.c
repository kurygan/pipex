/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:42:25 by mkettab           #+#    #+#             */
/*   Updated: 2025/04/04 02:01:07 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_env(char **env)
{
	int		i;
	int		j;
	char	*subbed;
	char	*path;

	i = -1;
	path = ft_strdup("PATH");
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		subbed = ft_substr(env[i], 0, j);
		if (ft_strcmp(subbed, path) == 0)
			return (free(subbed), free(path), env[i] + j + 1);
		free(subbed);
	}
	free(path);
	return (NULL);
}

char	*set_path(char *command, char **env)
{
	int		i;
	char	*exec;
	char	*path;
	char	*env_got;
	char	**allpath;

	i = -1;
	if (!command || !command[0])
		return (ft_strdup(""));
	if (command[0] == '/' && !access(command, F_OK | X_OK))
		return (ft_strdup(command));
	env_got = get_env(env);
	if (!env_got)
		return (ft_strdup(command));
	allpath = ft_split(env_got, ':');
	while (allpath[i++])
	{
		path = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path, command);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_freetab(allpath), exec);
		free(exec);
	}
	return (ft_freetab(allpath), ft_strdup(command));
}
