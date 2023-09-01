/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:32:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/08/24 14:34:24 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../gnl/get_next_line.h"

typedef struct s_env
{
	char	**paths;
	int		**pipes;
	pid_t	**pid_tab;
	int		fd_temp;
	char	**argvtab;
}	t_env;

/*EXEC*/

char	*ft_build_path(char *directory, char *cmd, t_env *env);
bool	ft_valid_directory(char **dir_paths, char *cmd, char **path, t_env *en);
void	ft_exec_slash_cmd(t_env *env, char **cmd_opt);
void	ft_exec_args(t_env *env, char *cmd, char **cmd_opt);
char	**ft_exec(t_env *env, char *cmd);

/*INIT*/

bool	ft_init_pipes(t_env *env);
bool	ft_init_paths(t_env *env, char **envp, char **argv);
bool	ft_init_env(t_env *env, char **envp, char **argv);
void	ft_cmd_not_found2(t_env *env, char *cmd, char **cmd_opt);

/*UTILS*/

void	ft_close_and_flush(t_env *env);
void	ft_close_pipe_fd(t_env *env, int *fd);
void	ft_structure_flush(t_env *env);
void	ft_flush_exit(t_env *env, char *error);
bool	ft_arg_not_empty(char *cmd);

/*UTILS_2*/

void	ft_close_and_flush_fd(t_env *env, int *fd, char *error);
bool	ft_has_env_path(char **envp);
bool	ft_cmd_has_slash(char *cmd);
bool	ft_argv_has_slash(char *cmd1, char *cmd2);
char	*ft_argv_without_slash(char **argv);

/*PIPEX*/

void	ft_no_such_file(t_env *env, char *cmd);
void	ft_close(int *fd);
void	child1(t_env *env, char **argv);
void	child2(t_env *env, char **argv);

#endif
