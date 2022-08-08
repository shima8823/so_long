/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:39:01 by shima             #+#    #+#             */
/*   Updated: 2022/06/08 13:14:49 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	chose_fmt(char c, va_list *ap, int *len, size_t *i);
static int	putunb_base(size_t nb, char *base, char c);
static int	putnb(int nb);
static void	putstr(va_list *ap, int *output_len);

int	ft_printf(const char *fmt, ...)
{
	int		len;
	size_t	i;
	va_list	ap;

	len = 0;
	i = 0;
	va_start(ap, fmt);
	errno = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
			chose_fmt(fmt[i + 1], &ap, &len, &i);
		else
			len += write(STDOUT_FILENO, &fmt[i++], 1);
		if (errno != 0 || len < 0)
			break ;
	}
	va_end(ap);
	if (errno != 0 || len < 0)
		return (-1);
	return (len);
}

static void	chose_fmt(char c, va_list *ap, int *len, size_t *i)
{
	unsigned char	uc;

	if (c == 'c')
	{
		uc = (unsigned char)va_arg(*ap, int);
		*len += write(STDOUT_FILENO, &uc, 1);
	}
	else if (c == 's')
		putstr(ap, len);
	else if (c == 'p')
		*len += putunb_base((size_t)va_arg(*ap, void *), "0123456789abcdef", c);
	else if (c == 'd' || c == 'i')
		*len += putnb(va_arg(*ap, int));
	else if (c == 'u')
		*len += putunb_base(va_arg(*ap, unsigned int), "0123456789", c);
	else if (c == 'x')
		*len += putunb_base(va_arg(*ap, unsigned int), "0123456789abcdef", c);
	else if (c == 'X')
		*len += putunb_base(va_arg(*ap, unsigned int), "0123456789ABCDEF", c);
	else if (c == '%')
		*len += write(STDOUT_FILENO, "%", 1);
	if (c == '\0')
		(*i)++;
	else
		(*i) += 2;
}

static int	putunb_base(size_t nb, char *base, char c)
{
	size_t	base_len;
	size_t	i;
	char	result[18];

	base_len = ft_strlen(base);
	if (nb == 0)
	{
		if (c == 'p')
			return (write(STDOUT_FILENO, "0x0", 3));
		return (write(STDOUT_FILENO, "0", 1));
	}
	i = 0;
	while (nb != 0)
	{
		result[17 - i++] = base[nb % base_len];
		nb /= base_len;
	}
	if (c == 'p')
	{
		result[17 - i - 1] = '0';
		result[17 - i] = 'x';
		i += 2;
	}
	return (write(STDOUT_FILENO, &result[17 - i + 1], i));
}

static int	putnb(int nb)
{
	size_t	i;
	char	result[11];

	i = 0;
	if (nb == 0)
		return (write(STDOUT_FILENO, "0", 1));
	else if (nb > 0)
	{
		while (nb != 0)
		{
			result[10 - i++] = '0' + (nb % 10);
			nb /= 10;
		}
	}
	else
	{
		while (nb != 0)
		{
			result[10 - i++] = '0' - (nb % 10);
			nb /= 10;
		}
		result[10 - i++] = '-';
	}
	return (write(STDOUT_FILENO, &result[10 - i + 1], i));
}

static void	putstr(va_list *ap, int *output_len)
{
	const char	*s;
	size_t		len;

	s = va_arg(*ap, const char *);
	if (!s)
	{
		*output_len += write(STDOUT_FILENO, "(null)", 6);
		return ;
	}
	len = ft_strlen(s);
	while (len > INT_MAX)
	{
		*output_len += write(STDOUT_FILENO, s, INT_MAX);
		if (errno != 0 || *output_len < 0)
			return ;
		s += INT_MAX;
		len -= INT_MAX;
	}
	*output_len += write(STDOUT_FILENO, s, len);
}
