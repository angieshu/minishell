/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 00:39:10 by ashulha           #+#    #+#             */
/*   Updated: 2017/04/23 00:39:11 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_conv(va_list *ap, t_flags *f, t_length *l)
{
	if (f->conv == 's' || f->conv == 'S')
		return (ft_ps(ap, f, l));
	else if (f->conv == 'c' || f->conv == 'C')
		return (ft_pc(ap, f, l));
	else if (f->conv == 'd' || f->conv == 'i' || f->conv == 'D')
		return (ft_pd(ap, f, l));
	else if (f->conv == 'u' || f->conv == 'U')
		return (ft_pu(ap, f, l));
	else if (f->conv == 'o' || f->conv == 'O')
		return (ft_po(ap, f, l));
	else if (f->conv == 'x' || f->conv == 'X')
		return (ft_px(ap, f, l));
	else if (f->conv == '%')
		return (ft_pper());
	else if (f->conv == 'e' || f->conv == 'E')
		return (ft_pe(ap, f, l));
	else if (f->conv == 'f' || f->conv == 'F')
		return (ft_pf(ap, f, l));
	else if (f->conv == 'p')
		return (ft_pp(ap, f));
	return (ft_pg(ap, f, l));
}

char	*ft_build(va_list *ap, t_flags *f, t_length *l)
{
	char *s;

	if (f->star == 1)
		ft_star(ap, f);
	s = ft_conv(ap, f, l);
	s = ft_min_width(s, f);
	s = ft_flags(s, f);
	return (s);
}
