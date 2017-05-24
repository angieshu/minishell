/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:42:35 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/22 18:42:36 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_cmd[] = {
	"cd", "echo", "env", "setenv", "unsetenv", "pwd", "exit",
	"emacs", "vim", "mkdir", "ls", "rm", "rmdir", "clear",
	"locate", "touch", "man", "mv", "gcc", "cat", (char*)NULL
};

static char	*command_generator(const char *text, int state)
{
	static int	i;
	static int	len;
	char		*name;

	if (!state)
	{
		i = 0;
		len = ft_strlen(text);
	}
	while (g_cmd[i] && (name = g_cmd[i]))
	{
		i++;
		if (ft_strncmp(name, text, len) == 0)
			return (ft_strdup(name));
	}
	return ((char *)NULL);
}

static char	**ash_complition(const char *text, int start, int end)
{
	char **matches;

	matches = NULL;
	(void)end;
	if (start == 0)
		matches = rl_completion_matches(text, command_generator);
	return (matches);
}

void		initialize_readline(void)
{
	rl_readline_name = "minishell";
	rl_attempted_completion_function = ash_complition;
}
