/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:08:34 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/17 17:08:36 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char **s, int j, char **env)
{
	int			k;

	k = 0;
	while (s[j][k])
	{
		if (s[j][k] == '"' || s[j][k] == '\'' || s[j][k] == '\\')
			k++;
		if (!s[j][k])
			break ;
		if ((s[j][k] == '$' || s[j][k] == '~') &&
			(k = check_env(s[j], k, env)) == -1)
			return (-1);
		else
			(s[j][k] ? ft_printf("%c", s[j][k]) : 0);
		k++;
	}
	return (0);
}

int			read_args(char **args, int j, char **env)
{
	while (args[j])
	{
		if (check_arg(args, j, env) == -1)
			return (-1);
		(args[++j]) ? ft_printf(" ") : 0;
	}
	return (0);
}

int			check_str(char **args, int j, char **env)
{
	char *s;

	s = NULL;
	if (args[j][0])
	{
		if (read_args(args, j, env) == -1)
			return (-1);
	}
	return (0);
}

char		**echo_cmd(char **a, char **env)
{
	int		i;
	int		j;
	int		new_line;

	i = 1;
	j = 0;
	if (!a[1] || !a[1][0])
	{
		ft_printf("\n");
		return (env);
	}
	new_line = (!ft_strncmp("-n", a[++j], PATH_MAX)) ? 1 : 0;
	(new_line) ? j++ : 0;
	check_str(a, j, env);
	(new_line) ? 0 : ft_printf("\n");
	return (env);
}
