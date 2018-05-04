/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:45:53 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 19:54:24 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_hexa(char *str)
{
	char	*s2;
	char	*s1;
	int		len;

	s2 = ft_convert_base(str, "0123456789", "0123456789abcdef");
	if (s2 != NULL)
	{
		len = ft_strlen(s2);
		len += 2;
		s1 = ft_strnew(len);
		if (s1 != NULL)
		{
			ft_strcpy(s1, "0x");
			ft_strcpy(s1 + 2, s2);
		}
		free(s2);
		return (s1);
	}
	return (NULL);
}

char		*ft_ptoa(void *ptr)
{
	char	*s1;
	char	*s2;

	if (ptr == NULL)
	{
		s1 = ft_strnew(3);
		if (s1 != NULL)
			ft_strcpy(s1, "0x0");
		return (s1);
	}
	else
	{
		s1 = ft_sizetoa((unsigned long int)ptr);
		if (s1 != NULL)
		{
			s2 = get_hexa(s1);
			free(s1);
			return (s2);
		}
	}
	return (NULL);
}
