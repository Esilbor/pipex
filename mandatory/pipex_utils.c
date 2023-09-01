/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:14:53 by bbresil           #+#    #+#             */
/*   Updated: 2023/08/22 11:52:06 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	free (env->pipes);
}

void	ft_close_and_flush(t_env *env)
{
	close(env->pipes[0][0]);
	env->pipes[0][0] = 0;
	close(env->pipes[0][1]);
	env->pipes[0][1] = 0;
	ft_structure_flush(env);
}

void	ft_flush_exit(t_env *env, char *error)
{
	ft_structure_flush(env);
	if (error)
	{
		ft_putstr_fd2(error, 2);
		ft_putstr_fd2("\n", 2);
	}
	exit(EXIT_FAILURE);
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

void	ft_close_pipe_fd(t_env *env, int *fd)
{
	close(env->pipes[0][0]);
	env->pipes[0][0] = 0;
	close(env->pipes[0][1]);
	env->pipes[0][1] = 0;
	close(*fd);
	*fd = 0;
}
