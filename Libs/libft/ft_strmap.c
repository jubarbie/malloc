/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 18:35:32 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 16:56:53 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*s2;

	i = 0;
	s2 = NULL;
	if (s && f)
	{
		s2 = ft_strnew(ft_strlen(s));
		if (!s2)
			return (NULL);
		while (s[i])
		{
			s2[i] = f(s[i]);
			i++;
		}
	}
	return (s2);
}
