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

int		checkEnv(char **args, char **buf, int i)
{
	char *s;
	
	(findEnv(*args)[0] != 0) ? s = findEnv(*args) : 0;
	while (*s)
		(*buf)[i++] = *(s++);
	while (**args && **args != '"' && **args != '\'')
		(*args)++;
	return (i);
}

char	quotes(char **s, char q)
{
	while (**s == '"' || **s == '\'')
	{
		if (q == **s)
			q = 0;
		else if (!q)
			q = **s;
		else
			break ;
		(*s)++;
	}
	return (q);
}

int		checkArg(char **s, char **buf, int flag)
{
	int i;
	static char q;

	(q != '"' && q != '\'') ? (q = 0) : 0;
	i = ft_strlen(*buf);
	while (**s)
	{
		if (**s == '\\' && !*(++(*s)))
			break ;
		q = quotes(s, q);
		(**s == '$' || **s == '~') ?
		(i = checkEnv(s, buf, i)) : ((**s) ? ((*buf)[i++] = **s) : 0);
		(*s)++;
	}
	if (!(q && flag))
		return (0);
	(*buf)[i++] = '\n';
	ft_printf("dquote> ");
	return (checkString(s, buf));
}

int		readArgs(char **args, char **buf)
{
	int i;
	int flag;

	flag = 0;
	while (*args)
	{
		(*(args + 1)) ? (flag = 0) : (flag = 1);
		if (checkArg(args, buf, flag) == -1)
			return (-1);
		i = ft_strlen(*buf);
		(*(++args)) ? ((*buf)[i++] = ' ') : 0;
	}
	return (0);
}

int		checkString(char **args, char **buf)
{
	int i;
	char *s;

	s = NULL;
	(!*buf) ? *buf = ft_strnew(PATH_MAX) : 0;
	if (**args)
	{
		if (readArgs(args, buf) == -1)
			return (-1);
	}
	else
	{
		get_next_line(0, &s);
		if (checkArg(&s, buf, 1) == -1)
			return (-1);	
	}
	return (0);
}

int		echo_cmd(char **args)
{
	int i;
	int newLine;
	char *buf;
	char **a;

	a = args;

	i = 1;
	buf = NULL;
	if (!a[1] || !a[1][0])
	{
		ft_printf("\n");
		return (1);
	}
	newLine = (!ft_strncmp("-n", *(++a), PATH_MAX)) ? 1 : 0;
	(newLine) ? (a)++ : 0;
	if (checkString(a, &buf) == -1)
		return (-1);
	ft_printf("%s", (!buf) ? "" : buf);
	(newLine) ? 0 : ft_printf("\n");
	// (buf) ? free(buf) : 0;
	return (1);
}
