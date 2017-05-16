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
# include <limits.h>
# define PROMPT (printf("%s ", "💥"))
# define SPACES " \t\n\r\a"
# define DELIM "|;"

void	*ft_realloc(void *ptr, size_t size);
char	**ft_strtok(char *s, char *sep);



#endif