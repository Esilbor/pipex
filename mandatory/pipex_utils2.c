/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:51:17 by bbresil           #+#    #+#             */
/*   Updated: 2023/07/26 12:06:03 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_close_and_flush_fd(t_env *env, int *fd, char *error)
{
	ft_close_pipe_fd(env, fd);
	ft_flush_exit(env, error);
}

bool	ft_has_env_path(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (true);
		envp++;
	}
	return (false);
}

bool	ft_cmd_has_slash(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (true);
	return (false);
}

bool	ft_argv_has_slash(char *cmd1, char *cmd2)
{
	if (ft_strchr(cmd1, '/') && ft_strchr(cmd2, '/'))
		return (true);
	return (false);
}

char	*ft_argv_without_slash(char **argv)
{
	int	i;

	i = 2;
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '/'))
			return (argv[i]);
		argv++;
	}
	return (NULL);
}
