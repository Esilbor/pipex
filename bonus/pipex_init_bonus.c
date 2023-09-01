/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:05 by bbresil           #+#    #+#             */
/*   Updated: 2023/08/25 10:47:32 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

bool	ft_init_pipes(t_env *env)
{
	env->pipes = malloc(sizeof(int *) * 2);
	if (!env->pipes)
		return (false);
	env->pipes[0] = malloc(sizeof(int) * 2);
	if (!env->pipes[0])
		return (free(env->pipes), false);
	env->pipes[1] = malloc(sizeof(int) * 2);
	if (!env->pipes[1])
		return (free(env->pipes[0]), free(env->pipes), false);
	env->pipes[0][0] = 0;
	env->pipes[0][1] = 0;
	env->pipes[1][0] = 0;
	env->pipes[1][1] = 0;
	return (true);
}

void	ft_dup2_failed(t_env *env)
{
	ft_putstr_fd("dup2 failed\n", 2);
	ft_close_and_flush(env);
	exit (1);
}

bool	ft_init_paths(t_env *env, char **envp, char **argv)
{
	env->paths = NULL;
	if (ft_has_env_path(envp))
	{
		while (*envp)
		{
			if (!ft_strncmp(*envp, "PATH=", 5))
			{
				env->paths = ft_split(*envp + 5, ':');
				if (!env->paths)
				{
					ft_putstr_fd("could not get env variables\n", 2);
					return (false);
				}
				return (true);
			}
			envp++;
		}
		return (true);
	}
	if (ft_argv_has_slash(env, argv))
		return (true);
	return (false);
}

bool	ft_init_env(t_env *env, char **envp, char **argv)
{
	int	i;

	i = 0;
	if (!ft_init_paths(env, envp, argv))
	{
		while (i < env->arc - 1)
		{
			if (!ft_cmd_has_slash(argv[i + 2]))
				ft_cmd_not_found(argv[i + 2]);
			i ++;
		}
		return (false);
	}
	if (!ft_init_pipes(env))
	{
		ft_free_tab((void **)env->paths);
		ft_putstr_fd("no pipes\n", 2);
		return (false);
	}
	if (!ft_init_pidtab(env, env->arc - 3))
		return (ft_structure_flush(env), false);
	return (true);
}

bool	ft_init_pidtab(t_env *env, int cmd_nb)
{
	int	i;

	i = 0;
	env->pid_tab = malloc(sizeof(pid_t) * (cmd_nb + 1));
	if (!env->pid_tab)
		return (false);
	while (i < cmd_nb)
	{
		env->pid_tab[i] = 0;
		i ++;
	}
	env->pid_tab[i] = 0;
	return (true);
}
