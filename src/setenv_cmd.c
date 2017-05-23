/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 23:17:09 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/18 23:17:11 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace(char **args, char **env)
{
	int i;

	i = -1;
	while (!(!ft_strncmp(env[++i], args[1], ft_strlen(args[1]))
						&& env[i][ft_strlen(args[1])] == '='));
	ft_strclr(env[i]);
	ft_strcat(env[i], args[1]);
	ft_strcat(env[i], "=");
	ft_strcat(env[i], args[2]);
	return (1);
}

static void	createNew(char **args, char **env)
{
	char ***e;
	char **envp;
	int i;

	i = -1;
	e = &env;
	while ((*e)[++i]);
	envp = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = -1;
	while ((*e)[++i])
		envp[i] = ft_strdup((*e)[i]);
	// free(env);
	envp[i] = (char*)ft_memalloc(PATH_MAX + 1);
	ft_strncat(envp[i], args[1], ft_strlen(args[1]));
	ft_strncat(envp[i], "=", 1);
	ft_strncat(envp[i], args[2], ft_strlen(args[2]));
	e = &envp;
	i = -1;
	while ((*e)[++i])
	{
		*env = (*e)[i];
		env++;
	}
}

static int	oneArg(char **args, char **env)
{
	int i;
	int j;
	char **a;

	i = (args[1][0] == '"');
	j = 0;
	a = (char**)ft_memalloc(sizeof(char*) * 3);
	a[0] = NULL;
	a[1] = ft_strnew(sizeof(args[1]));
	a[2] = ft_strnew(sizeof(args[1]));
	while (args[1][i] != '=' && args[1][i])
		a[1][j++] = args[1][i++];
	if (!args[1][i])
		return (1);
	j = 0;
	while (args[1][++i] != '"' && args[1][i])
		a[2][j++] = args[1][i];
	setenv_cmd(a, env);
	free(a);
	return (1);
}

int			setenv_cmd(char	**args, char **env)
{

	if (!args[1])
		return (1);
	if (!args[2])
		return (oneArg(args, env));
	if (findEnv(args[1], env)[0] != 0)
		return (replace(args, env));
	createNew(args, env);
	return (1);
}