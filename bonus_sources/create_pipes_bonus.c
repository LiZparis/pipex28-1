/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:11:40 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 20:25:26 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_struct_prog(t_prog *prog, char **argv, char **envp)
{
	prog->infile = -1;
	prog->outfile = -1;
	prog->pid = -1;
	prog->num_cmd = 0;
	prog->pipes = NULL;
	prog->num_pipes = 0;
	prog->is_first_cmd = 0;
	prog->is_last_cmd = 0;
	prog->exit_status = 0;
	prog->argv = argv;
	prog->envp = envp;
	prog->length = 50;
	prog->here_doc = 0;
	prog->exec.path_env = NULL;
	prog->exec.paths = NULL;
	prog->exec.full_path = NULL;
	prog->exec.access_ok = NULL;
	prog->exec.i = 0;
}

void	ft_dup_error(t_prog *prog, int index)
{
	if (index == prog->is_first_cmd)
		ft_putstr_fd("Failed to duplicate infile to stdin\n", 2);
	else if (index == prog->is_last_cmd)
		ft_putstr_fd("Failed to duplicate stdout to outfile\n", 2);
	else if (index > prog->is_first_cmd && index < prog->is_last_cmd)
		ft_putstr_fd("Failed to duplicate pipe\n", 2);
	ft_close(prog);
	exit(EXIT_FAILURE);
}

void	create_pipes(t_prog *prog)
{
	int	i;

	prog->num_pipes = prog->num_cmd - 1;
	prog->pipes = malloc(sizeof(int *) * prog->num_pipes);
	if (!prog->pipes)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < prog->num_pipes)
	{
		prog->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(prog->pipes[i]) == -1)
		{
			perror("Failed to create pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_param(t_prog *prog, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (argc >= 6 && (ft_strncmp(argv[1], "here_doc", 8) == 0)
		&& argv[1][8] == '\0')
	{
		prog->here_doc = 1;
		prog->num_cmd = argc - 4;
		prog->is_first_cmd = 3;
		prog->is_last_cmd = argc - 2;
	}
	else if (argc < 6 && (ft_strncmp(argv[1], "here_doc", 8) == 0)
		&& argv[1][8] == '\0')
	{	
		ft_putstr_fd("Usage: ./pipex here_doc delimiter cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		prog->num_cmd = argc - 3;
		prog->is_first_cmd = 2;
		prog->is_last_cmd = argc - 2;
	}
}
