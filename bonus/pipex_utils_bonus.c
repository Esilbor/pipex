/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:14:57 by bbresil           #+#    #+#             */
/*   Updated: 2023/07/25 22:17:29 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_structure_flush(t_env *env)
{
	int	i;

	i = 0;
	if (env->paths)
	{
		while (env->paths[i])
		{
			free(env->paths[i]);
			i ++;
		}
		free (env->paths);
	}
	free (env->pipes[0]);
	free (env->pipes[1]);
	free (env->pid_tab);
	free (env->pipes);
}

void	ft_flush_exit(t_env *env, char *error)
{
	ft_structure_flush(env);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_close_fd(int *fd)
{
	if (*fd)
	{
		close(*fd);
		*fd = 0;
	}
}

void	ft_close_pipe_fd(int *pipe)
{
	ft_close_fd(&pipe[0]);
	ft_close_fd(&pipe[1]);
}

bool	ft_arg_not_empty(char *cmd)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen2(cmd);
	if (!cmd)
		return (false);
	while (i < len)
	{
		if (cmd[i] != ' ')
			return (true);
		i++;
	}
	return (false);
}
