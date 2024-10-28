/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:14:34 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 12:18:53 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	path_env_error(char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

void	ft_close(t_prog *prog)
{
	if (prog->infile != -1)
	{
		close(prog->infile);
		prog->infile = -1;
	}
	if (prog->outfile != -1)
	{
		close(prog->outfile);
		prog->outfile = -1;
	}
	if (prog->pipe_fd[0] != -1)
	{
		close(prog->pipe_fd[0]);
		prog->pipe_fd[0] = -1;
	}
	if (prog->pipe_fd[1] != -1)
	{
		close(prog->pipe_fd[1]);
		prog->pipe_fd[1] = -1;
	}
}

void	is_last_cmd(t_prog *prog)
{
	ft_close(prog);
	exit(127);
}
