/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:18:40 by bbresil           #+#    #+#             */
/*   Updated: 2023/09/01 09:26:59 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_no_such_file(t_env *env, char *cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	ft_structure_flush(env);
	exit (1);
}

void	ft_close(int *fd)
{
	if (*fd)
	{
		close(*fd);
		*fd = 0;
	}
}

void	child1(t_env *env, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_close_pipe_fd(env, &fd);
		ft_no_such_file(env, argv[1]);
	}
	if (dup2(fd, 0) < 0)
		ft_close_and_flush_fd(env, &fd, "dup2 failed");
	if (dup2(env->pipes[0][1], 1) < 0)
		ft_close_and_flush_fd(env, &fd, "dup2 failed");
	ft_close_pipe_fd(env, &fd);
	ft_exec(env, argv[2]);
}

void	child2(t_env *env, char **argv)
{
	int		fd;

	fd = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
	if (fd < 0)
	{
		ft_close_pipe_fd(env, &fd);
		ft_no_such_file(env, argv[4]);
	}
	if (dup2(env->pipes[0][0], 0) < 0)
		ft_close_and_flush_fd(env, &fd, "dup2 failed");
	if (dup2(fd, 1) < 0)
		ft_close_and_flush_fd(env, &fd, "dup2 failed");
	ft_close_pipe_fd(env, &fd);
	ft_exec(env, argv[3]);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_putstr_fd2("invalid arg nb\n", 2), 1);
	if (!ft_init_env(&env, envp, argv))
		return (1);
	if (pipe(env.pipes[0]) < 0)
		return (ft_flush_exit(&env, strerror(errno)), 1);
	pid1 = fork();
	if (pid1 < 0)
		return (ft_close_and_flush(&env), 1);
	if (!pid1)
		child1(&env, argv);
	pid2 = fork();
	if (pid2 < 0)
		return (ft_close_and_flush(&env), 1);
	if (!pid2)
		child2(&env, argv);
	close(env.pipes[0][0]);
	close(env.pipes[0][1]);
	ft_structure_flush(&env);
	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);
}
