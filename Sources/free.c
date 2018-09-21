/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/06 17:21:12 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*unalloc_block(t_block *b)
{
	if (b == NULL)
	 	return (NULL);
	if (is_b_alloc(b))
		set_b_free(b);
	return (b);
}

void pthsafe_free(void *ptr)
{
	t_block	*b;

	b = (t_block *)ptr;
	b = find_block(ptr);
	if (b != NULL)
		if (unalloc_block(b) == NULL)
			ft_putendl("Trying to free block that was not allocated");
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	pthsafe_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
