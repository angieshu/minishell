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

#include "minishell.h"

static void create_env(char ***env)
{
	int i;
	int j;

	i = -1;
	while (environ[++i]);
	(*env) = (char**)ft_memalloc(sizeof(char*) * i);
	i = -1;
	while (environ[++i])
	{
		(*env)[i] = (char*)ft_memalloc(PATH_MAX + 1);
		j = -1;
		while (environ[i][++j])
			(*env)[i][j] = environ[i][j];
		(*env)[i][j] = 0;
	}
	(*env)[i] = NULL;
	i = -1;
}

static void	prompt(char **env)
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
	ft_printf(BOLD"%s ", (buf[0] == '~') ? buf :
				(buf + ((last_slash) ? (last_slash + 1) : 0)));
}

int		main()
{
	char *line;
	char **comands;
	char **args;
	char **env;
	int status;

	status = 1;
	create_env(&env);
	while (status)
	{
		prompt(env);
		set_dir(env, "PWD");
		initialize_readline();
		line = readline(YEL"⇢  "RESET);
		if (!line || !*line)
			continue ;
		comands = ft_strtok(line, ";");
		while (*comands)
		{
			args = ft_strtok(*comands, SPACES);
			add_history(line);
			rl_bind_key('\t', rl_complete);
			status = execution(args, env);
			free(*comands);
			comands++;
			(args) ? free(args) : 0;
		}
		free(line);
	}
	free(env);
}
