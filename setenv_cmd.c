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

static void	replaceAndAllocate(char **args, int flag)
{
	int i;
	int j;
	char **en;
	char ***env;
	
	i = 0;
	j = -1;
	while (environ[i++]);
	(en) = (char**)ft_memalloc(sizeof(*environ) * (i + 1));
	i = -1;
	while (*environ)
		(en)[++i] = ft_strdup(*(environ++));
	env = &en;
	i = -1;
	while (!(!ft_strncmp((*env)[++i], args[1], ft_strlen(args[1]))
							&& (*env)[i][ft_strlen(args[1])] == '='));
	(*env)[i] = (char*)ft_realloc((*env)[i],
							sizeof(args[1]) + sizeof(args[2]) + 2);
	while (*(args[1]))
		(*env)[i][++j] = *(args[1]++);
	(*env)[i][++j] = '=';
	while (*(args[2]))
		(*env)[i][++j] = *(args[2]++);
	(*env)[i][++j] = 0;
	environ = *env;
}

static int	replace(char **args, int flag)
{
	char *s;
	char **p;
	int i;
	
	i = -1;
	s = findEnv(args[1]);
	args[2] += (args[2][0] == '=');
	p = &s;
	if (ft_strlen(*p) >= ft_strlen(args[2]))
	{
		ft_strclr(*p);
		while (args[2][++i])
			*(*p)++ = args[2][i];
		s = *p;
		return (flag);
	}
	replaceAndAllocate(args, flag);
	return (1);
}

static void	createNew(char **args, int flag)
{
	int i;
	int j;
	char ***env;
	char **e;

	i = 0;
	e = environ; 
	while (environ[i++]);
	*env = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = -1;
	while (*environ)
		(*env)[++i] = ft_strdup(*(environ++));
	(*env)[++i] = ft_strnew(sizeof(args[1]) + sizeof(args[2]) + 2);
	j = -1;
	while (*(args[1]))
		(*env)[i][++j] = *(args[1]++);
	(*env)[i][++j] = '=';
	while (*(args[2]))
		(*env)[i][++j] = *(args[2]++);
	(*env)[i][++j] = 0;
	(*env)[++i] = NULL;
	(flag == 1) ? free_env(e) : 0;
	environ = *env;
}

static int	oneArg(char **args, int flag)
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
		return ((flag) ? 1 : 0);
	j = 0;
	while (args[1][++i] != '"' && args[1][i])
		a[2][j++] = args[1][i];
	flag = setenv_cmd(a);
	free(a);
	return (flag);
}

int			setenv_cmd(char	**args)
{

	static int flag;

	(flag != 0 && flag != 1) ? (flag = 0) : 0;
	if (!args[1])
		return (flag + 1);
	if (!args[2])
		flag = oneArg(args, flag);
	else if (findEnv(args[1])[0] != 0)
		flag = replace(args, flag);
	else
	{
		createNew(args, flag);
		flag = 1;
	}
	return (flag + 1);
}