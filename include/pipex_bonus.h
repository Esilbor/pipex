/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:32:47 by bbresil           #+#    #+#             */
/*   Updated: 2023/09/01 10:30:43 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	pid_t	*pid_tab;
	int		fd_temp;
	int		arc;
	char	**argvtab;
}	t_env;

// /*EXEC*/

char	*ft_build_path(char *directory, char *cmd, t_env *env);
bool	ft_valid_directory(char **dir_paths, char *cmd,
			char **path, t_env *env);
void	ft_exec_slash_cmd(t_env *env, char **cmd_opt);
void	ft_exec_args(t_env *env, char *cmd, char **cmd_opt);
char	**ft_exec(t_env *env, char *cmd);

// /*INIT*/

bool	ft_init_pipes(t_env *env);
void	ft_dup2_failed(t_env *env);
bool	ft_init_paths(t_env *env, char **envp, char **argv);
bool	ft_init_env(t_env *env, char **envp, char **argv);
bool	ft_init_pidtab(t_env *env, int cmd_nb);

// /*UTILS*/

void	ft_structure_flush(t_env *env);
void	ft_flush_exit(t_env *env, char *error);
void	ft_close_fd(int *fd);
void	ft_close_pipe_fd(int *pipe);
bool	ft_arg_not_empty(char *cmd);

// /*UTILS_2*/

bool	ft_has_env_path(char **envp);
bool	ft_argv_has_slash(t_env *env, char **argv);
bool	ft_cmd_has_slash(char *cmd);
void	ft_cmd_not_found(char *cmd);
void	ft_cmd_not_found2(t_env *env, char *cmd, char **cmd_opt);

// /*OPEN*/

void	ft_close_and_flush(t_env *env);
void	ft_no_such_file(t_env *env, char *cmd);
int		ft_open_infile(char **argv, t_env *env, int i);
int		ft_open_outfile(int i, char **argv, t_env *env);
int		ft_open(int i, char **argv, t_env *env);

// /*PIPEX*/

void	ft_dup2(t_env *env, char **argv, int fd, int i);
void	ft_free_cmd_opt(char **cmd_opt);
pid_t	ft_child(t_env *env, char **argv, int i);
void	ft_wait(t_env *env);

#endif
