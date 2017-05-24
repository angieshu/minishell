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
# define CD_ERNOTEXIST(p, e) ({ft_printf(NOTEXIST, p); return (e);})
# define CD_ERNOTDIR(p, e) ({ft_printf(NOTDIR, p); return (e);})
# define CD_ERPERM(p, e) ({ft_printf(NOPERM, p); return (e);})
# define CD_ERNOPWD(p, e) ({ft_printf(NOPWD, p); return (e);})

char	*find_env(char *name, char **env);
int		read_args(char **args, int j, char **env);
int		check_str(char **args, int j, char **env);
void	set_dir(char **env, char *dirname);
int		check_env(char *args, int k, char **env);

void	initialize_readline(void);
char	**execution(char **args, char **env);
void	free_env(char **env);

char	**launch(char **args, char **env);
char	**echo_cmd(char **args, char **env);
char	**cd_cmd(char	**args, char **env);
char	**setenv_cmd(char	**args, char **env);
char	**unsetenv_cmd(char **args, char **env);
char	**env_cmd(char **args);
char	**exit_cmd(char **env);
char	**pwd_cmd(char **args, char **env);

#endif
