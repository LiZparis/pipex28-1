/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:17:46 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 12:18:30 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_struct_prog(t_prog *prog)
{
	prog->infile = -1;
	prog->outfile = -1;
	prog->pipe_fd[0] = -1;
	prog->pipe_fd[1] = -1;
	prog->pid1 = -1;
	prog->pid2 = -1;
	prog->exit_status = 0;
	prog->exec.i = 0;
	prog->exec.path_env = NULL;
	prog->exec.paths = NULL;
	prog->exec.full_path = NULL;
	prog->exec.access_ok = NULL;
}

void	check_infile(t_prog *prog, char *infile)
{
	prog->infile = open(infile, O_RDONLY);
	if (prog->infile < 0)
	{
		if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		{
			perror(infile);
			ft_close(prog);
			exit(0);
		}
	}
}

void	check_outfile(t_prog *prog, char *outfile)
{
	prog->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (prog->outfile < 0)
	{
		if (errno == EACCES)
		{
			perror(outfile);
			ft_close(prog);
			exit(1);
		}
		else
		{
			perror(outfile);
			ft_close(prog);
			exit(0);
		}
	}
}
