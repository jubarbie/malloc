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

static char is_overflowing(size_t n1, size_t n2, size_t res)
{
    if (n1 != 0 && res / n1 != n2)
        return (1);
    return (0);
}
void        *calloc(size_t nmemb, size_t size)
{
    t_block *block;
    size_t  alsize;

    pthread_mutex_lock(&g_mutex);
	debug_calloc(nmemb, size);
    alsize = nmemb * size;
    if (size == 0 || nmemb == 0)
        return (NULL);
    if (is_overflowing(nmemb, size, alsize))
        return (NULL);
	block = dispatch_alloc(alsize);
    ft_bzero(payload_addr(block), get_b_size(block));
    debug_return(block);
	pthread_mutex_unlock(&g_mutex);
	return (payload_addr(block));
}
