/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhang2 <lzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:30:51 by lzhang2           #+#    #+#             */
/*   Updated: 2024/10/28 21:18:20 by lzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
// # include <string.h>
# include <fcntl.h>
# include <unistd.h>
// unlink
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../libraries/Libft/libft.h"

typedef struct s_find_exec
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*access_ok;
	int		i;
}	t_find_exec;

typedef struct s_prog
{
	int			infile;
	int			outfile;
	int			pid;
	int			num_cmd;
	int			**pipes;
	int			num_pipes;
	int			is_first_cmd;
	int			is_last_cmd;
	char		temp_file[50];
	int			length;
	int			exit_status;
	char		**argv;
	char		**envp;
	int			here_doc;
	t_find_exec	exec;
}	t_prog;

/*pipex_bonus.c*/
void	get_exit_status(t_prog *prog);
void	ft_child(t_prog *prog, int index);
void	execute_children(t_prog *prog);

/*creat_pipes_bonus.c*/
void	init_struct_prog(t_prog *prog, char **argv, char **envp);
void	create_pipes(t_prog *prog);
void	ft_dup_error(t_prog *prog, int index);
void	check_param(t_prog *prog, int argc, char **argv);

/*check_files_bonus.c*/
void	write_temp_file(const char *limiter, int fd, char *temp_file);
void	handle_here_doc(const char *limiter, char *temp_file);
void	check_infile(t_prog *prog);
void	check_outfile(t_prog *prog, char *outfile);
// void	prepare_files(t_prog *prog, int argc, char **argv);

/*find_executable_bonus.c*/
char	*ft_get_path_env(char **envp);
char	*build_full_path(const char *dir, const char *command);
char	*find_executable(t_prog *prog, char **command, char **envp);

/*free_close_message.c*/
void	close_pipes(t_prog *prog);
void	ft_close(t_prog *prog);
void	ft_free_split(char **split);
void	path_env_error(char *command);
void	is_last_cmd(t_prog *prog);

/*execute_command_bonus.c*/
void	is_execvable(t_prog *prog, char *path, char **args, char **envp);
char	*is_accessible(t_prog *prog, char *command, char **args);
void	execute_abs_cmd(t_prog *prog, char **args, char **envp);
void	execute_relative_cmd(t_prog *prog, char **args, char **envp);
void	execute_command(t_prog *prog, char *cmd, char **envp);
#endif