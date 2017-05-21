/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 16:53:58 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/14 16:53:59 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void		free_env(char **env)
{
	int i;

	i = 0;
	// while (env[i])
	// 	free(env[i++]);
	free(env);
	env = NULL;
}

int		pwd_cmd(char **args)
{
	char buf[PATH_MAX + 1];
	int i;

	i = 0;
	while (args[i])
		i++;
	(i > 1) ? ft_printf("pwd: too many arguments\n") : 0;
	(i == 1) ? ft_printf("%s\n", getcwd(buf, PATH_MAX)) : 0;
	return (1);
}

char	*findEnv(char *name, char **env)
{
	int i;
	char *p;

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

void create_env(char ***env)
{
	int i;

	i = -1;
	while (environ[++i]);
	(*env) = (char**)ft_memalloc(sizeof(char*) * i);
	i = -1;
	while (environ[++i])
	{
		(*env)[i] = ft_strdup(environ[i]);
	}
	(*env)[i] = NULL;
	i = -1;
}

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

void	prompt(char **env)
{
	int i;
	int last_slash;
	char buf[PATH_MAX];

	i = -1;
	while (++i < PATH_MAX)
		buf[i] = 0;
	getcwd(buf, PATH_MAX);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '/')
			last_slash = i;
	}
	if (!ft_strcmp(buf, findEnv("$HOME", env)))
	{
		i = -1;
		while ((buf[++i]))
			buf[i] = 0;
		buf[0] = '~';
	}
	ft_printf(BOLD"%s "RESET, (buf[0] == '~') ? buf :
						(buf + ((last_slash) ? (last_slash + 1) : 0)));
	// ft_printf(BOLD YEL"⇢  "RESET);
}

int		main()
{
	char *line;
	char **args;
	char **env;
	int status;

	status = 1;
	create_env(&env);
	int i = -1;
	while (status)
	{
		prompt(env);
		rl_bind_key('\t', rl_complete);
		// get_next_line(0, &line);
		line = readline(BOLD YEL"⇢  "RESET);
		if (!line || !*line)
			continue ;
		args = ft_strtok(line, SPACES);
		add_history(line);
		status = execution(args, env);
		if (!line || !*line)
			continue ;
		free(line);
		// (line) ? free(line) : 0;
		// (args) ? free(args) : 0;
	}
	free_env(env);
}
