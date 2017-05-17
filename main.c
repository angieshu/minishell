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

// int		pwd_cmd(char **args)

// int		help_cmd(char **args)

char	*find_env(char **envp, char *name)
{
	int i;

	i = -1;
	(ft_strlen(name) == 1 && name[0] == '~') ? name = "$HOME" : 0;
	name++;
	while (envp[++i])
	{
		if (!ft_strncmp(name, envp[i], ft_strlen(name)))
			if (envp[i][ft_strlen(name)] == '=')
				return (ft_strchr(envp[i], '=') + 1);
	}
	return ("");
}

int		exit_cmd()
{
	return (0);
}

int		env_cmd(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (1);
}

// int		unsetenv_cmd(char **args)

// int		setenv_cmd(char	**args)

int		echo_cmd(char **args, char **envp)
{
	int i;
	int newLine;

	i = 1;
	(args[1][0] == '$') ? printf("%s", find_env(envp, args[i++])) : 0;
	newLine = (!ft_strncmp("-n", args[1], PATH_MAX)) ? 1 : 0;
	(newLine) ? i++ : 0;
	while (args[i])
	{
		(i == 1) ? 0 : printf(" ");
		printf("%s", (args[i][0] == '\\') ? (args[i] + 1) : args[i]);
		i++;
	}
	(newLine) ? 0 : printf("\n");
	return (1);
}

int		cd_cmd(char	**args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("cd: string not in pwd: %s\n", args[1]);
		return (1);
	}
	if (((i == 0) ? (chdir("~/")) : (chdir(args[1]))) == -1)
	{
		// (EACCES) ? printf("cd: permission denied: %s\n", args[1]) : 0;
		// (ENOENT) ? printf("cd: no such file or directory: %s\n", args[1]) : 0;
		// (ENOTDIR) ? printf("cd: not a directory: %s\n", args[1]) : 0;
		return (1);
	}
	return (1);
}

int		execution(char **args, char **envp)
{
	if (!args)
		return (1);
	(!ft_strncmp(args[0], "/bin/", 5)) ? (args[0] += 5) : 0;
	if (!ft_strncmp(args[0], "cd", PATH_MAX))
		return (cd_cmd(args));
	if (!ft_strncmp(args[0], "echo", PATH_MAX))
		return(echo_cmd(args, envp));
	if (!ft_strncmp(args[0], "env", PATH_MAX))
		return(env_cmd(envp));
	if (!ft_strncmp(args[0], "exit", PATH_MAX))
		return(exit_cmd());
	// else
	// 	printf()
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	char *line;
	char **args;
	int status;

	av = 0;
	ac = 0;
	status = 1;
	while (status)
	{
		ft_putstr(YEL"➣  "RESET);
		get_next_line(0, &line);
		args = (!line[0]) ? NULL : ft_strtok(line, SPACES);
		status = execution(args, envp);
		free(line);
		free(args);
	}
}
