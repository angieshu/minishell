/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:01:52 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/14 17:01:56 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../includes/libft/libft.h"
# include "../includes/gnl/get_next_line.h"
# include "../includes/ft_printf/src/libftprintf.h"
# include <limits.h>
# include <crt_externs.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# define YEL	"\x1B[33m"
# define RESET	"\x1B[0m"
# define BOLD	"\e[1m"
# define SPACES " \t\n\r\a\""
# define NOTEXIST "cd: no such file or directory: %s\n"
# define NOTDIR "cd: not a directory: %s\n"
# define NOPERM "cd: permission denied: %s\n"
# define NOPWD "cd: string not in pwd: %s\n"
# define CD_ERNOTEXIST(p) ({ft_printf(NOTEXIST, p); return (1);})
# define CD_ERNOTDIR(p) ({ft_printf(NOTDIR, p); return (1);})
# define CD_ERPERM(p) ({ft_printf(NOPERM, p); return (1);})
# define CD_ERNOPWD(p) ({ft_printf(NOPWD, p); return (1);})

extern char **environ;

char	*findEnv(char *name, char **env);
int		echo_cmd(char **args, char **env);
int		readArgs(char **args, char **buf, char **env);
int		checkString(char **args, char **buf, char **env);
void	set_dir(char **env, char *dirname);
int		checkEnv(char **args, char **buf, int i, char **env);

void	initialize_readline(void);
int		execution(char **args, char **env);
int		launch(char **args, char **env);
/*
---------------- ⚡︎ Commands ⚡︎----------------
*/

int		cd_cmd(char	**args, char **env);
int		setenv_cmd(char	**args, char **env);
int		unsetenv_cmd(char **args, char **env);
int		env_cmd(char **args);
int		exit_cmd();
int		pwd_cmd(char **args);

#endif