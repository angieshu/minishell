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

// int		setenv_cmd(char **args, char ***env)
// {
// 	char **new_env;
// 	char **ep;
// 	size_t size;
// 	size_t name;
// 	size_t value;

// 	size = -1;
// 	ep = *env;
// 	name = ft_strlen(args[1]);
// 	value = ft_strlen(args[2]) + 1;
// 	while ((ep)[++size])
// 	{
// 		if (!ft_strncmp((ep)[size], args[1], name) && (ep)[size][name] == '=')
// 			break;
// 	}
// 	if (!ep[size])
// 	{
// 		new_env = (char**)ft_realloc(*ep, sizeof(char*) * (size + 2));
// 		if (!new_env)
// 			return (-1);
// 	}
// 	new_env[size] = (char*)ft_memalloc(name + value + 1);
// 	if (!new_env[size])
// 	{
// 		free((char*)new_env);
// 		return (-1);
// 	}
// 	ft_memcpy(new_env[size], args[1], name);
// 	new_env[size][name] = '=';
// 	ft_memcpy(&new_env[size][name + 1], args[2], value);
// 	// new_env[size + 1] = NULL;
// 	ep = new_env;
// 	env = &ep;
// 	int i = -1;
// 	// while (new_env[++i])
// 	// 	ft_printf("%s\n", new_env[i]);
// 	return (1);
// }

static int	replace(char **args, char **env)
{
	int i;

	i = -1;
	while (!(!ft_strncmp(env[++i], args[1], ft_strlen(args[1]))
						&& env[i][ft_strlen(args[1])] == '='));
	// free(env[i]);
	env[i] = ft_strnew(ft_strlen(args[1] + ft_strlen(args[2]) + 1));
	ft_strcat(env[i], args[1]);
	ft_strcat(env[i], "=");
	ft_strcat(env[i], args[2]);
	return (1);
}

static void	createNew (char **args, char **env)
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
	// free_env(env);
	envp[i] = (char*)ft_memalloc(ft_strlen(args[1] + ft_strlen(args[2]) + 2));
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

// static void	createNew(char **args, char **env)
// {
// 	int i;
// 	char ***e;

// 	i = -1;
// 	while (env[++i]);
// 	*e = (char**)ft_realloc((**env), sizeof(char*) * (i + 1));
// 	i = -1;
// 	while ((*env)[++i])
// 		e[i] = ft_strdup((*env)[i]);
// 	// free_env(*env);
// 	// env = NULL;
// 	e[i] = ft_strnew(ft_strlen(args[1]) + ft_strlen(args[2]) + 1);
// 	ft_strcat(e[i], args[1]);
// 	ft_strcat(e[i], "=");
// 	ft_strcat(e[i], args[2]);
// 	e[++i] = NULL;
// 	*env = e;
// 	i = -1;
// 	while (e[++i])
// 		(*env)[i] = e[i];
// }

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
	free(a[1]);
	free(a[2]);
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