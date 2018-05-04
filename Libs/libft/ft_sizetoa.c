/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizetoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 11:33:44 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 16:00:02 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long int	ft_power_long(unsigned long int n, int power)
{
	unsigned long int res;

	res = n * n;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	if (power > 2)
		res = n * (ft_power_long(n, --power));
	return (res);
}

static size_t	ft_nbrlen(unsigned long int n)
{
	if (n == 0)
		return (0);
	return (1 + ft_nbrlen(n / 10));
}

static char		*do_itoa(char *str, unsigned long int n, size_t len)
{
	char				*ps;
	unsigned long int	dig;

	ps = str;
	if (n == 0)
		*str = '0';
	while (len-- > 0)
	{
		dig = n / ft_power_long(10, len);
		*ps++ = dig + 48;
		n = n % ft_power_long(10, len);
	}
	return (str);
}

char			*ft_sizetoa(unsigned long int n)
{
	size_t	len;
	char	*str;

	str = NULL;
	len = ft_nbrlen(n);
	if (n == 0)
		len = 1;
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	str = do_itoa(str, n, len);
	return (str);
}
