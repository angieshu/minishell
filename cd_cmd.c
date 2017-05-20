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

int		cd_cmd(char	**a)
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
		ft_strncat(p, findEnv("~"), PATH_MAX);
	else if ((*a)[0] == '~' && (*a)[1] == '/' && ft_strlen(*a) > 2)
		ft_strncat(p, (*a + 1), ft_strlen(*a));
	else if (!ft_strcmp(*a, "-"))
		ft_printf("%s\n", ft_strncat(p, findEnv("$OLDPWD"), PATH_MAX));
	else
		ft_strncat(p, *a, PATH_MAX);
	(!(access(p, F_OK) == -1)) ? (lstat(p, &s)) : CD_ERNOTEXIST(p);
	(!(access(p, R_OK) == -1)) ? 0 : CD_ERPERM(p);
	(!S_ISDIR(s.st_mode)) ? CD_ERNOTDIR(p) : 0;
	chdir(p);
	return (1);
}