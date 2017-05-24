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

char	**cd_cmd(char **a, char **env)
{
	char		p[PATH_MAX + 1];
	struct stat	s;
	int			i;

	i = -1;
	while (++i < PATH_MAX)
		p[i] = 0;
	i = 0;
	while (a[i++])
		NULL;
	(i > 3) ? CD_ERNOPWD(a[1], env) : (a)++;
	if (!*a || !ft_strcmp(*a, "~") || ((*a)[0] == '~' && (*a)[1] == '/'))
		ft_strcat(p, find_env("~", env));
	if (*a && (*a)[0] == '~' && (*a)[1] == '/' && ft_strlen(*a) > 2)
		ft_strncat(p, (*a + 1), ft_strlen(*a));
	else if (*a && !ft_strcmp(*a, "-"))
		ft_printf("%s\n", ft_strcat(p, find_env("$OLDPWD", env)));
	else if (*a && (*a)[0] != '~' && (*a)[0] != '-')
		ft_strncat(p, *a, PATH_MAX);
	(!(access(p, F_OK) == -1)) ? (lstat(p, &s)) : CD_ERNOTEXIST(p, env);
	(!(access(p, R_OK) == -1)) ? 0 : CD_ERPERM(p, env);
	(!S_ISDIR(s.st_mode)) ? CD_ERNOTDIR(p, env) : 0;
	set_dir(env, "OLDPWD");
	chdir(p);
	return (env);
}
