/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:37:52 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/22 17:37:53 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*findEnv(char *name, char **env)
{
	int i;

	i = -1;
	(ft_strlen(name) == 1 && name[0] == '~') ? name = "$HOME" : 0;
	name += (name[0] == '$');
	while (env[++i])
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
			if (env[i][ft_strlen(name)] == '=')
				return (ft_strchr(env[i], '=') + 1); 
	}
	return ("");
}

void	set_dir(char **env, char *dirname)
{
	char **a;

	a = (char**)ft_memalloc(sizeof(char*) * 4);
	a[0] = NULL;
	a[1] = ft_strdup(dirname);
	a[2] = ft_strnew(PATH_MAX);
	getcwd(a[2], PATH_MAX);
	a[3] = 0;
	setenv_cmd(a, env);
	free(a);
}

int		checkEnv(char **args, char **buf, int i, char **env)
{
	char *s;
	
	(findEnv(*args, env)[0] != 0) ? s = findEnv(*args, env) : 0;
	if (findEnv(*args, env)[0] == 0)
		return (-1);
	while (*s)
		(*buf)[i++] = *(s++);
	while (**args && **args != '"' && **args != '\'')
		(*args)++;
	return (i);
}
