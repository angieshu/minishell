/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:24:51 by ashulha           #+#    #+#             */
/*   Updated: 2017/05/15 16:24:54 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char *new_ptr;

	if (ptr && !size)
	{
		if (!(new_ptr = (char*)ft_memalloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return(new_ptr);
	}
	if (!(new_ptr = (char*)ft_memalloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (new_ptr);
}