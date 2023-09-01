/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:21:36 by bbresil           #+#    #+#             */
/*   Updated: 2023/09/01 10:29:56 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_dup2(t_env *env, char **argv, int fd, int i)
{
	if (!i)
	{
		if (dup2(fd, 0) == -1)
			ft_dup2_failed(env);
		if (dup2(env->pipes[i % 2][1], 1) == -1)
			ft_dup2_failed(env);
	}
	else if (!argv[i + 4])
	{
		if (dup2(env->pipes[(i + 1) % 2][0], 0) == -1)
			ft_dup2_failed(env);
		if (dup2(fd, 1) == -1)
			ft_dup2_failed(env);
	}
	else
	{
		if (dup2(env->pipes[(i + 1) % 2][0], 0) == -1)
			ft_dup2_failed(env);
		if (dup2(env->pipes[i % 2][1], 1) == -1)
			ft_dup2_failed(env);
	}
	ft_close_fd(&fd);
	ft_close_pipe_fd(env->pipes[0]);
	ft_close_pipe_fd(env->pipes[1]);
}

void	ft_free_cmd_opt(char **cmd_opt)
{
	int	i;

	i = 0;
	while (cmd_opt[i])
	{
		free (cmd_opt[i]);
		i ++;
	}
}

pid_t	ft_child(t_env *env, char **argv, int i)
{
	pid_t	pid;
	int		fd;

	fd = 0;
	if (argv[i + 4])
	{
		if (pipe(env->pipes[i % 2]) < 0)
			ft_flush_exit(env, strerror(errno));
	}
	pid = fork();
	if (pid < 0)
		return (ft_close_and_flush(env), pid);
	if (!pid)
	{
		fd = ft_open(i, argv, env);
		ft_dup2(env, argv, fd, i);
		ft_exec(env, argv[i + 2]);
	}
	if (i)
		ft_close_pipe_fd(env->pipes[(i + 1) % 2]);
	return (pid);
}

void	ft_wait(t_env *env)
{
	int	i;

	i = 0;
	while (i < (env->arc - 2) && env->pid_tab[i])
	{
		waitpid(env->pid_tab[i], NULL, 0);
		i ++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	int		i;
	pid_t	last_pid;

	i = 0;
	if (argc < 5)
		return (ft_putstr_fd("invalid arg nb\n", 2), 1);
	env.arc = argc - 1;
	if (!ft_init_env(&env, envp, argv))
		return (1);
	while (i < argc - 3)
	{
		last_pid = ft_child(&env, argv, i);
		env.pid_tab[i] = last_pid;
		i ++;
	}
	ft_wait(&env);
	ft_structure_flush(&env);
	return (0);
}
