/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:18:42 by bbresil           #+#    #+#             */
/*   Updated: 2023/07/26 13:40:08 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

bool	ft_argv_has_slash(t_env *env, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j <= env->arc - 3)
	{
		if (ft_strchr(argv[i + 2], '/'))
			i ++;
		j ++;
	}
	if (i == env->arc - 2)
		return (true);
	return (false);
}

// bool	ft_argv_has_slash(t_env *env, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (i < env->arc - 1)
// 	{
// 		if (ft_strchr(argv[i + 2], '/'))
// 			return (true);
// 		i ++;
// 	}
// 	return (false);
// }

bool	ft_cmd_has_slash(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (true);
	return (false);
}

void	ft_cmd_not_found(char *cmd)
{
	char	**cmd_tab;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab)
		return ;
	ft_putstr_fd("pipex_bonus : command not found: ", 2);
	ft_putstr_fd(cmd_tab[0], 2);
	ft_putstr_fd("\n", 2);
	ft_free_tab((void **)cmd_tab);
}

void	ft_cmd_not_found2(t_env *env, char *cmd, char **cmd_opt)
{
	ft_putstr_fd("pipex_bonus: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_free_tab((void **)cmd_opt);
	ft_flush_exit(env, NULL);
}
