/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:19:46 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 21:43:08 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	wait_for_children(int num_cmd)
{
	int		status;
	int		exit_status;
	pid_t	pid;
	int		i;

	exit_status = 0;
	i = 0;
	while (i < num_cmd)
	{
		pid = wait(&status);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		else
			perror("waitpid failed");
		i++;
	}
	return (exit_status);
}

void	ft_child(t_prog *prog, int index)
{
	if (index == prog->is_first_cmd)
	{
		check_infile(prog);
		if ((dup2(prog->infile, STDIN_FILENO) == -1) || (dup2(prog->pipes[index
						- prog->is_first_cmd][1], STDOUT_FILENO) == -1))
			ft_dup_error(prog, index);
	}
	else if (index > prog->is_first_cmd && index < prog->is_last_cmd)
	{
		if ((dup2(prog->pipes[index - prog->is_first_cmd - 1][0], STDIN_FILENO)
			== -1) || (dup2(prog->pipes[index
			- prog->is_first_cmd][1], STDOUT_FILENO) == -1))
			ft_dup_error(prog, index);
	}
	else if (index == prog->is_last_cmd)
	{
		check_outfile(prog, prog->argv[prog->num_cmd + 1]);
		if (dup2(prog->pipes[index - prog->is_first_cmd - 1][0], STDIN_FILENO)
			== -1 || dup2(prog->outfile, STDOUT_FILENO) == -1)
			ft_dup_error(prog, index);
	}
	ft_close(prog);
	execute_command(prog, prog->argv[index], prog->envp);
}

void	execute_children(t_prog *prog)
{
	int		index;

	index = prog->is_first_cmd;
	while (index <= prog->is_last_cmd)
	{
		prog->pid = fork();
		if (prog->pid == 0)
		{
			ft_child(prog, index);
			exit(EXIT_SUCCESS);
		}
		else if (prog->pid < 0)
		{
			perror("fork failed");
			ft_close(prog);
			exit(EXIT_FAILURE);
		}
		index++;
	}
}

static void	generate_random_filename(char *temp_file, int length)
{
	const char		random_base[] = "abcdefg!#$%^&*()_+ABCDEF123456789";
	size_t			random_base_size;
	unsigned long	seed;
	size_t			i;

	seed = (unsigned long)&temp_file;
	random_base_size = sizeof(random_base) - 1;
	ft_strlcpy(temp_file, "/tmp/.my_temp_file_", length);
	i = ft_strlen(temp_file);
	while (i < (size_t)length - 1)
	{
		seed = (seed * 1103515245 + 12345) % 4294967296;
		temp_file[i] = random_base[seed % random_base_size];
		i++;
	}
	temp_file[length - 1] = '\0';
	if (access(temp_file, F_OK) == 0)
		generate_random_filename(temp_file, length);
}

int	main(int argc, char **argv, char **envp)
{
	t_prog	prog;

	init_struct_prog(&prog, argv, envp);
	generate_random_filename(prog.temp_file, prog.length);
	init_struct_prog(&prog, argv, envp);
	check_param(&prog, argc, argv);
	create_pipes(&prog);
	execute_children(&prog);
	unlink(prog.temp_file);
	ft_close(&prog);
	prog.exit_status = wait_for_children(prog.num_cmd);
	return (prog.exit_status);
}

/*strace -e signal=SIGPIPE -o trace.log < input /usr/bin/cat
| /usr/bin/wcgd > output
*/
/*valgrind --leak-check=full --show-leak-kinds=all 
--trace-children=yes ./pipex input /usr/bin/cat dls output
*/