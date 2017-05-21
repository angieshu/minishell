/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 19:04:38 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/18 19:04:40 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_old_pwd(char **env)
{
	char **a;
	char buf[PATH_MAX + 1];
	int i;

	if (!ft_strncmp(findEnv("PWD", env), getcwd(buf, PATH_MAX), ft_strlen(findEnv("PWD", env))))
		return ;
	a = (char**)ft_memalloc(sizeof(char*) * 4);
	a[0] = NULL;
	a[1] = ft_strdup("OLDPWD");
	a[2] = ft_strnew(PATH_MAX);
	getcwd(a[2], PATH_MAX);
	a[3] = 0;
	setenv_cmd(a, env);
	free(a);
	a = NULL;
}

int		cd_cmd(char	**a, char **env)
{
	char p[PATH_MAX + 1];
	struct stat s;
	int i;

	i = -1;
	while (++i < PATH_MAX)
		p[i] = 0;
	i = 0;
	while (a[i++]);
	(i > 3) ? CD_ERNOPWD(a[1]) : 0;
	(a)++;
	if (!*a || !ft_strcmp(*a, "~") || ((*a)[0] == '~' && (*a)[1] == '/'))
		ft_strcat(p, findEnv("~", env));
	if (*a && (*a)[0] == '~' && (*a)[1] == '/' && ft_strlen(*a) > 2)
		ft_strncat(p, (*a + 1), ft_strlen(*a));
	else if (*a && !ft_strcmp(*a, "-"))
		ft_printf("%s\n", ft_strcat(p, findEnv("$OLDPWD", env)));
	else if (*a && (*a)[0] != '~' && (*a)[0] != '-')
		ft_strncat(p, *a, PATH_MAX);
	(!(access(p, F_OK) == -1)) ? (lstat(p, &s)) : CD_ERNOTEXIST(p);
	(!(access(p, R_OK) == -1)) ? 0 : CD_ERPERM(p);
	(!S_ISDIR(s.st_mode)) ? CD_ERNOTDIR(p) : 0;
	set_old_pwd(env);
	chdir(p);
	return (1);
}