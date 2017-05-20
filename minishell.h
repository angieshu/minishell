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
# include "includes/libft/libft.h"
# include "includes/gnl/get_next_line.h"
# include "includes/ft_printf/src/libftprintf.h"
# include <limits.h>
# include <crt_externs.h>
# include <sys/stat.h>
# define RED	"\x1B[31m"
# define YEL	"\x1B[33m"
# define CYN	"\x1B[36m"
# define RESET	"\x1B[0m"
# define BOLD	"\e[1m"
# define PROMPT (ft_printf(BOLD RED"❖"RESET))
# define SPACES " \t\n\r\a"
# define DELIM "|;"
# define CD_ERNOTEXIST(p) ({ft_printf("cd: no such file or directory: %s\n", p); return (1);})
# define CD_ERNOTDIR(p) ({ft_printf("cd: not a directory: %s\n", p); return (1);})
# define CD_ERPERM(p) ({ft_printf("cd: permission denied: %s\n", p); return (1);})
# define CD_ERNOPWD(p) ({ft_printf("cd: string not in pwd: %s\n", p); return (1);})


extern char **environ;

void	*ft_realloc(void *ptr, size_t size);
char	**ft_strtok(char *s, char *sep);
char	*findEnv(char *name);
int		echo_cmd(char **args);
int		checkString(char **args, char **buf);
int		readArgs(char **args, char **buf);
int		cd_cmd(char	**args);
int		setenv_cmd(char	**args);
void	free_env(char **env);
int		unsetenv_cmd(char **args);
#endif