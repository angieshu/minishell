/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:41:33 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/19 16:41:35 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unsetenv_cmd(char **args, char **env)
{
	int i;

	i = -1;
	(args[1]) ? (args[1] += (args[1][0] == '$')) : 0;
	if (args[1] && findEnv(args[1], env)[0] != 0)
	{
		while (!(!ft_strncmp(env[++i], args[1], ft_strlen(args[1]))
				&& env[i][ft_strlen(args[1])] == '='));
		i--;
		while (env[++i])
			env[i] = env[i + 1];
		env[i] = NULL;
	}
	return (1);
}
