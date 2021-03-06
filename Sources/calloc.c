/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:38:21 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 21:40:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static char	is_overflowing(size_t n1, size_t n2, size_t res)
{
	if (n1 != 0 && res / n1 != n2)
		return (1);
	return (0);
}

static void	*pthsafe_calloc(size_t nmemb, size_t size)
{
	t_block	*block;
	void	*ptr;
	size_t	alsize;

	debug_calloc(nmemb, size);
	alsize = nmemb * size;
	if (alsize == 0)
		block = dispatch_alloc(1);
	else if (is_overflowing(nmemb, size, alsize))
		return (NULL);
	else
		block = dispatch_alloc(alsize);
	ptr = payload_addr(block);
	if (ptr != NULL)
		ft_bzero(ptr, get_b_size(block));
	else
		errno = ENOMEM;
	debug_block(block);
	return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = pthsafe_calloc(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
