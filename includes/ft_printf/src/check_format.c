/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 00:47:14 by ashulha           #+#    #+#             */
/*   Updated: 2017/04/23 00:47:17 by ashulha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_check_conv_type(char **format, t_flags *f, t_length *l)
{
	if (**format == 'L')
	{
		l->lll = 1;
		(*format)++;
	}
	if (**format != 's' && **format != 'd' && **format != 'i' &&
		**format != 'o' && **format != 'S' && **format != 'p' &&
		**format != 'D' && **format != 'O' && **format != 'u' &&
		**format != 'U' && **format != 'x' && **format != 'X' &&
		**format != 'c' && **format != 'C' && **format != 'f' &&
		**format != 'F' && **format != 'e' && **format != 'E' &&
		**format != '%' && **format != 'n' && **format != '%')
		return (0);
	f->conv = **format;
	return (1);
}

int		ft_check_minwith(char **format, va_list *ap, t_flags *f)
{
	int i;

	if (f->star == 1)
	{
		f->star--;
		ft_star(ap, f);
		return (1);
	}
	i = ft_atoi(*format);
	*format += ft_count_num(*format);
	if (i > 0)
	{
		f->min_width = i;
		return (1);
	}
	return (0);
}

int		ft_check_precision(va_list *ap, char **format, t_flags *f)
{
	if (**format == '.')
	{
		*format += 1;
		if (**format == '*')
		{
			f->precision = (int)va_arg(*ap, intmax_t);
			if (f->precision < 0)
				f->precision = -1;
			*format += 1;
			return (1);
		}
		else if (f->star != 1)
		{
			f->precision = ft_atoi(*format);
			*format += ft_count_num(*format);
			if (f->precision < 0)
				return (0);
		}
		return (1);
		f->precision = -1;
	}
	return (0);
}

void	ft_check_t_length(char **f, t_length *l)
{
	if (**f == 'h')
	{
		(*f)++;
		if (**f == 'h')
			l->hh = 1;
		else
			l->h = 1;
	}
	else if (**f == 'l')
	{
		(*f)++;
		if (**f == 'l')
			l->ll = 1;
		else
			l->l = 1;
	}
	else if (**f == 'j' || **f == 'z')
	{
		if (**f == 'j')
			l->j = 1;
		else if (**f == 'z')
			l->z = 1;
		(*f)++;
	}
	l->none = 1;
}

char	*ft_check_format(char **format, va_list *ap, t_flags *f, t_length *l)
{
	*format += 1;
	if (!**format)
		return (NULL);
	while (!ft_check_conv_type(format, f, l))
	{
		ft_check_t_length(format, l);
		if (ft_check_flag(format, f))
			continue ;
		else if (ft_check_minwith(format, ap, f))
			continue ;
		else if (ft_check_precision(ap, format, f))
			continue ;
		else
			break ;
	}
	ft_check_t_length(format, l);
	if (!ft_check_conv_type(format, f, l))
		return (ft_invalid(format, f));
	return (ft_build(ap, f, l));
}
