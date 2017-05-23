/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:28:30 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/22 17:28:31 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execution(char **args, char **env)
{
	if (!args || !*args || !**args)
		return (1);
	else if (!ft_strncmp(args[0], "cd", PATH_MAX))
		return (cd_cmd(args, env));
	else if (!ft_strncmp(args[0], "echo", PATH_MAX))
		return (echo_cmd(args, env));
	else if (!ft_strncmp(args[0], "env", PATH_MAX))
		return (env_cmd(env));
	else if (!ft_strncmp(args[0], "setenv", PATH_MAX))
		return (setenv_cmd(args, env));
	else if (!ft_strncmp(args[0], "unsetenv", PATH_MAX))
		return (unsetenv_cmd(args, env));
	else if (!ft_strncmp(args[0], "pwd", PATH_MAX))
		return (pwd_cmd(args));
	else if (!ft_strncmp(args[0], "exit", PATH_MAX))
		return (exit_cmd());
	else
		return (launch(args, env));
	return (0);
}
