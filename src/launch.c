/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:16:56 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/20 10:17:01 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_error(char *p, char *arg)
{
	int i;
	int slash;

	i = -1;
	slash = 0;
	while (arg[++i])
	{
		if (arg[i] == '/')
			slash++;
	}
	if (slash > 0 && !p)
		ft_printf("ash: no such file or directory: %s\n", arg);
	else if (!p)
		ft_printf("ash: command not found: %s\n", arg);
}

static void	process(char *ex, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(ex, args, env) == -1)
			ft_printf("ash: permission denied: %s\n", ex);
		exit(-1);
	}
	else if (pid < 0)
	{
		ft_printf("ash: unable to fork process: %d\n", pid);
		exit(-1);
	}
	else
		wait(&pid);
}

static void	find_cmd(char **args, char **env)
{
	char **p;
	char *path;
	int i;
	
	i = -1;
	p = ft_strtok(findEnv("$PATH", env), ":");
	path = ft_strnew(PATH_MAX);
	while (p[++i])
	{
		ft_strclr(path);
		ft_strcat(path, p[i]);
		(args[0][0] == '/') ? 0 : ft_strcat(path, "/");
		ft_strcat(path, args[0]);
		if (access(path, F_OK) != -1)
		{
			process(path, args, env);
			break ;
		}
	}
	check_error(p[i], args[0]);
	i = -1;
	while (p[++i])
		free(p[i]);
	free(path);
	free(p);
}

int		launch(char **args, char **env)
{
	if (args[0] == NULL)
		return (1);
	(access(args[0], F_OK) != -1) ? process(args[0], args, env) :
											find_cmd(args, env);
	return (1);
}

