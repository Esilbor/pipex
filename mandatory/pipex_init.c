/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:16:55 by bbresil           #+#    #+#             */
/*   Updated: 2023/08/25 10:45:44 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	ft_init_pipes(t_env *env)
{
	env->pipes = malloc(sizeof(int *) * 1);
	if (!env->pipes)
		return (false);
	env->pipes[0] = malloc(sizeof(int) * 2);
	if (!env->pipes[0])
		return (free(env->pipes), false);
	env->pipes[0][0] = 0;
	env->pipes[0][1] = 0;
	return (true);
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
	if (ft_argv_has_slash(argv[2], argv[3]))
		return (true);
	return (false);
}

void	ft_cmd_not_found(char *cmd)
{
	char	**cmd_tab;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab)
		return ;
	ft_putstr_fd("pipex : command not found: ", 2);
	ft_putstr_fd(cmd_tab[0], 2);
	ft_putstr_fd("\n", 2);
	ft_free_tab((void **)cmd_tab);
}

bool	ft_init_env(t_env *env, char **envp, char **argv)
{
	if (!ft_init_paths(env, envp, argv))
	{
		if (!ft_cmd_has_slash(argv[2]))
			ft_cmd_not_found(argv[2]);
		if (!ft_cmd_has_slash(argv[3]))
			ft_cmd_not_found(argv[3]);
		return (false);
	}
	if (!ft_init_pipes(env))
	{
		ft_free_tab((void **)env->paths);
		ft_putstr_fd("no pipes\n", 2);
		return (false);
	}
	return (true);
}

void	ft_cmd_not_found2(t_env *env, char *cmd, char **cmd_opt)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_free_tab((void **)cmd_opt);
	ft_flush_exit(env, NULL);
}
