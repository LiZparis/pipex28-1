/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_message_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:14:34 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 21:39:05 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	close_pipes(t_prog *prog)
{
	int	i;

	if (prog->pipes)
	{
		i = 0;
		while (i < prog->num_pipes)
		{
			if (prog->pipes[i])
			{
				close(prog->pipes[i][0]);
				close(prog->pipes[i][1]);
				free(prog->pipes[i]);
			}
			i++;
		}
	}
	free(prog->pipes);
	prog->pipes = NULL;
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
	close_pipes(prog);
}

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

void	is_last_cmd(t_prog *prog)
{
	ft_close(prog);
	exit(0);
}
