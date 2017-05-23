/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:33:58 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/22 17:33:59 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_cmd()
{
	return (0);
}

int		env_cmd(char **env)
{
	int i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
	return (1);
}
