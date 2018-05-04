/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:32:23 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 14:11:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ptoa(void *ptr)
{
	char	*s1;
	char	*s2;
	int		len;

	if (ptr == NULL)
		return ("0x0");
	else
	{
		s1 = ft_sizetoa((unsigned long int)ptr);
		if (s1 != NULL)
		{
			s2 = ft_convert_base(s1, "0123456789", "0123456789abcdef");
			free(s1);
			if (s2 != NULL)
			{
				len = ft_strlen(s2);
				len += 2;
				s1 = ft_strnew(len);
				if (s1 != NULL)
				{
					ft_strcpy(s1, "0x");
					ft_strcpy(s1 + 2, s2);
					free(s2);
					return (s1);
				}
				free(s2);
				return (s1);
			}
		}
	}
	return (NULL);
}
