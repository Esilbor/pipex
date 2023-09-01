/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:03:28 by bbresil           #+#    #+#             */
/*   Updated: 2023/08/25 10:36:17 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*ft_build_path(char *directory, char *cmd, t_env *env)
{
	char	*path;

	path = malloc(sizeof(char) * ft_strlen2(directory) + ft_strlen2(cmd) + 2);
	if (!path)
		ft_flush_exit(env, "could not malloc path\n");
	ft_memcpy(path, directory, ft_strlen2(directory));
	path[ft_strlen2(directory)] = '/';
	ft_memcpy(path + ft_strlen2(directory) + 1, cmd, ft_strlen2(cmd));
	path[ft_strlen2(directory) + ft_strlen2(cmd) + 1] = 0;
	return (path);
}

bool	ft_valid_directory(char **dir_paths, char *cmd, char **path, t_env *env)
{
	while (*dir_paths)
	{
		*path = ft_build_path(*dir_paths, cmd, env);
		if (!*path)
			ft_flush_exit(env, "could not build directory\n");
		if (!access(*path, F_OK | X_OK | R_OK))
			return (true);
		free (*path);
		dir_paths++;
	}
	*path = NULL;
	return (false);
}

void	ft_exec_slash_cmd(t_env *env, char **cmd_opt)
{
	if (access(cmd_opt[0], F_OK | X_OK | R_OK))
	{
		ft_free_tab((void **)cmd_opt);
		ft_flush_exit(env, strerror(errno));
	}
	if (execve(cmd_opt[0], cmd_opt, env->paths) < 0)
	{
		ft_free_tab((void **)cmd_opt);
		ft_flush_exit(env, strerror(errno));
	}
}

void	ft_exec_args(t_env *env, char *cmd, char **cmd_opt)
{
	char	*cmd_directory;

	if (!cmd_opt)
	{
		ft_free_tab((void **)cmd_opt);
		ft_flush_exit(env, "could not split cmd");
	}
	if (!ft_strchr(cmd, '/'))
	{
		if (!ft_valid_directory(env->paths, cmd_opt[0],
				&cmd_directory, env))
			ft_cmd_not_found2(env, cmd, cmd_opt);
		if (execve(cmd_directory, cmd_opt, env->paths) < 0)
		{
			free (cmd_directory);
			ft_free_tab((void **)cmd_opt);
			ft_flush_exit(env, strerror(errno));
		}
	}
	else
		ft_exec_slash_cmd(env, cmd_opt);
}

char	**ft_exec(t_env *env, char *cmd)
{
	char	**cmd_opt;

	if (*cmd && ft_arg_not_empty(cmd))
	{
		cmd_opt = ft_split(cmd, ' ');
		ft_exec_args(env, cmd, cmd_opt);
	}
	else
		ft_flush_exit(env, "pipex_bonus: empty command");
	return (cmd_opt);
}
