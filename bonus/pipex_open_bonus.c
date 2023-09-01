/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:32:31 by bbresil           #+#    #+#             */
/*   Updated: 2023/09/01 10:28:33 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_close_and_flush(t_env *env)
{
	close(env->pipes[0][0]);
	env->pipes[0][0] = 0;
	close(env->pipes[0][1]);
	env->pipes[0][1] = 0;
	close(env->pipes[1][0]);
	env->pipes[1][0] = 0;
	close(env->pipes[1][1]);
	env->pipes[1][1] = 0;
	ft_structure_flush(env);
}

void	ft_no_such_file(t_env *env, char *cmd)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	ft_structure_flush(env);
	exit (1);
}

int	ft_open_infile(char **argv, t_env *env, int i)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_close_pipe_fd(env->pipes[i % 2]);
		ft_close_pipe_fd(env->pipes[(i + 1) % 2]);
		ft_no_such_file(env, argv[1]);
	}
	return (fd);
}

int	ft_open_outfile(int i, char **argv, t_env *env)
{
	int	fd;

	fd = open(argv[i + 3], O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
	if (fd < 0)
	{
		ft_close_pipe_fd(env->pipes[i % 2]);
		ft_close_pipe_fd(env->pipes[(i + 1) % 2]);
		ft_no_such_file(env, argv[env->arc]);
	}
	return (fd);
}

int	ft_open(int i, char **argv, t_env *env)
{
	int	fd;

	fd = 0;
	if (!i)
		fd = ft_open_infile(argv, env, i);
	else if (!argv[i + 4])
		fd = ft_open_outfile(i, argv, env);
	return (fd);
}
