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
	while (env[i])
		free(env[i++]);
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
// int		help_cmd(char **args)

char	*findEnv(char *name)
{
	int i;
	char *p;

	i = -1;
	(ft_strlen(name) == 1 && name[0] == '~') ? name = "$HOME" : 0;
	name += (name[0] == '$');
	while (environ[++i])
	{
		if (!ft_strncmp(name, environ[i], ft_strlen(name)))
			if (environ[i][ft_strlen(name)] == '=')
				return (ft_strchr(environ[i], '=') + 1); 
	}
	return ("");
}

int		exit_cmd(int flag)
{
	char ***en;

	if (flag > 1)
	{
		en = &environ;
		free_env(*en);
		free(en);
	}
	return (0);
}

int		env_cmd()
{
	int i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
	return (1);
}

int		execution(char **args)
{
	static int flag;
	int f;

	if (!args || !*args || !**args)
		f = 1;
	else if (!ft_strncmp(args[0], "cd", PATH_MAX))
		f = cd_cmd(args);
	else if (!ft_strncmp(args[0], "echo", PATH_MAX))
		f = echo_cmd(args);
	else if (!ft_strncmp(args[0], "env", PATH_MAX))
		f = env_cmd();
	else if (!ft_strncmp(args[0], "setenv", PATH_MAX))
		f = setenv_cmd(args);
	else if (!ft_strncmp(args[0], "unsetenv", PATH_MAX))
		f = unsetenv_cmd(args);
	else if (!ft_strncmp(args[0], "pwd", PATH_MAX))
		f = pwd_cmd(args);
	else if (!ft_strncmp(args[0], "exit", PATH_MAX))
		f = exit_cmd(flag);
	else
		f = launch(args);
	(f > flag) ? (flag = f) : 0;
	return (f);
}

void	prompt(void)
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
	if (!ft_strcmp(buf, findEnv("$HOME")))
	{
		i = -1;
		while ((buf[++i]))
			buf[i] = 0;
		buf[0] = '~';
	}
	// ft_printf(BOLD YEL"⚡︎"RESET);
	ft_printf(BOLD"%s "RESET, (buf[0] == '~') ? buf :
						(buf + ((last_slash) ? (last_slash + 1) : 0)));
	ft_printf(BOLD YEL"⇢  "RESET);
}

int		main()
{
	char *line;
	char **args;
	int status;
	int i;

	status = 1;
	ft_printf("\n");
	while (status)
	{
		i = -1;
		prompt();
		// ft_printf(BOLD YEL"⚡︎  "RESET);
		get_next_line(0, &line);
		if (!line || !*line)
			continue ;
		args = ft_strtok(line, SPACES);
		status = execution(args);
		(line) ? free(line) : 0;
		(args) ? free(args) : 0;
	}
}
