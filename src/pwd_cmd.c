/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 19:10:30 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/22 19:10:31 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pwd_cmd(char **args, char **env)
{
	char	buf[PATH_MAX + 1];
	int		i;

	i = 0;
	while (args[i])
		i++;
	(i > 1) ? ft_printf("pwd: too many arguments\n") : 0;
	(i == 1) ? ft_printf("%s\n", getcwd(buf, PATH_MAX)) : 0;
	return (env);
}
