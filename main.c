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
	(flag) ? free(environ) : 0;
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

// int		unsetenv_cmd(char **args)

// int		replace_existed(char **args, )

int		setenv_cmd(char	**args, int flag)
{
	// int i;
	// char *s;
	// char **p;
	// char ***en;

	// if (findEnv(environ, args[1])[0] != 0)
	// {
	// 	i = -1;
	// 	s = findEnv(environ, args[1]);
	// 	p = &s;
	// 	args[2] += (args[2][0] == '=');
	// 	if (ft_strlen(*p) >= ft_strlen(args[2]))
	// 	{
	// 		ft_strclr(*p);
	// 		while (args[2][++i])
	// 			**p++ = args[2][i];
	// 		s = *p;
	// 		return (1);
	// 	}
	// 	*p = (char*)ft_realloc(ft_strlen(args[2]) + 1);
	// 	ft_strclr(*p);
	// 	while (args[2][++i])
	// 		**p++ = args[2][i]; 
	// 	return (1);
	// }
	// else
	// {
	// 	i = 0;
	// 	en = &environ;
	// 	if (!flag)
	// 	{
	// 		while (environ[i++]);
	// 		*en = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	// 		ft_memcpy(*en, environ, sizeof(environ));
	// 		*en[i] = 
	// 	}

		// *environ = (char**)ft_realloc(*environ, sizeof(char*) * (i + 1));
		// environ[i] = ft_strnew(ft_strlen(args[1]) + ft_strlen(args[2]) + 1);
		// ft_strncat(environ[i], args[1], PATH_MAX);
		// ft_strncat(environ[i], "=", PATH_MAX);
		// ft_strncat(environ[i], args[2], PATH_MAX);
		// environ[++i] = NULL;
	return (1);

}






int		execution(char **args, int flag)
{
	if (!args)
		return (1);
	// (!ft_strncmp(args[0], "/bin/", 5)) ? (args[0] += 5) : 0;
	if (!ft_strncmp(args[0], "cd", PATH_MAX))
		return (cd_cmd(args));
	if (!ft_strncmp(args[0], "echo", PATH_MAX))
		return(echo_cmd(args));
	if (!ft_strncmp(args[0], "env", PATH_MAX))
		return(env_cmd());
	if (!ft_strncmp(args[0], "setenv", PATH_MAX))
		return(setenv_cmd(args, flag));
	if (!ft_strncmp(args[0], "pwd", PATH_MAX))
		return(pwd_cmd(args));
	if (!ft_strncmp(args[0], "exit", PATH_MAX))
		return(exit_cmd(flag));
	// else
	// 	ft_printf()
	return (0);
}

int		main()
{
	char *line;
	char **args;
	int status;
	int flag;

	flag = 0;
	status = 1;
//UNSETENV OLDPWD TO CUR DIR

	while (status)
	{
		ft_printf(BOLD YEL"⚡︎ "RESET);
		get_next_line(0, &line);
		args = (!line[0]) ? NULL : ft_strtok(line, SPACES);
		status = execution(args, flag);
		(line) ? free(line) : 0;
		(args) ? free(args) : 0;
	}
}
