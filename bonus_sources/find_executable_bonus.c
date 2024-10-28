/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:30:39 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/25 21:52:52 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*ft_get_path_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*build_full_path(const char *dir, const char *command)
{
	char	*full_path;

	full_path = malloc(ft_strlen(dir) + ft_strlen(command) + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	return (full_path);
}

char	*find_executable(t_prog *prog, char **command, char **envp)
{
	prog->exec.path_env = ft_get_path_env(envp);
	if (!prog->exec.path_env)
		path_env_error(*command);
	prog->exec.paths = ft_split(prog->exec.path_env, ':');
	if (!prog->exec.paths)
		return (NULL);
	while (prog->exec.paths [prog->exec.i])
	{
		prog->exec.full_path = build_full_path(prog
				->exec.paths[prog->exec.i], *command);
		if (prog->exec.full_path)
		{
			prog->exec.access_ok = is_accessible(prog,
					prog->exec.full_path, command);
			if (prog->exec.access_ok)
			{
				ft_free_split(prog->exec.paths);
				return (prog->exec.access_ok);
			}
			free(prog->exec.full_path);
		}
		prog->exec.i++;
	}
	ft_free_split(prog->exec.paths);
	return (NULL);
}
