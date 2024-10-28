/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:11:55 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 21:04:34 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	is_execvable(t_prog *prog, char *path, char **args, char **envp)
{
	if (execve(path, args, envp) == -1)
	{
		ft_free_split(args);
		ft_close(prog);
		exit(127);
	}
}

char	*is_accessible(t_prog *prog, char *command, char **args)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == -1)
		{
			perror(command);
			ft_free_split(args);
			ft_close(prog);
			exit(126);
		}
		return (command);
	}
	return (NULL);
}

void	execute_abs_cmd(t_prog *prog, char **args, char **envp)
{
	char	*access_ok;

	access_ok = is_accessible(prog, args[0], args);
	if (access_ok)
		is_execvable(prog, access_ok, args, envp);
	else
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_free_split(args);
		is_last_cmd(prog);
	}
}

void	execute_relative_cmd(t_prog *prog, char **args, char **envp)
{
	char	*path;

	path = NULL;
	path = find_executable(prog, args, envp);
	if (!path)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		ft_free_split(args);
		is_last_cmd(prog);
	}
	is_execvable(prog, path, args, envp);
}

void	execute_command(t_prog *prog, char *cmd, char **envp)
{
	char	**args;

	args = NULL;
	while (*cmd == ' ')
		cmd++;
	if (!*cmd)
	{
		ft_putstr_fd(": Command not found\n", 2);
		is_last_cmd(prog);
	}
	args = ft_split(cmd, ' ');
	if (!args)
	{
		ft_putstr_fd("Error: Failed to split command\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strchr(cmd, '/'))
		execute_abs_cmd(prog, args, envp);
	else
		execute_relative_cmd(prog, args, envp);
}
