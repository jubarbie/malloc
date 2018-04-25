/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:29:48 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 11:39:41 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	defragment(void *min, void *max, void *ptr)
{
	size_t	size;

	while (prev_block(ptr) >= min && hdb_alloc(prev_block(ptr)) == 0)
	{
		ptr = prev_block(ptr);
		if (ptr == min)
		{
			break ;
		}
	}
	while (next_block(ptr) < max && hdb_alloc(next_block(ptr)) == 0)
	{
		size = hdb_size(ptr) + hdb_size(next_block(ptr));
		set_hdb(ptr, size, 0);
		set_ftb_size(ptr, size);
	}
}

void		ft_free(void *ptr)
{
	void	*p;

	p = g_mem_tiny;
	while ((char *)p < (char *)zone_limit(g_mem_tiny))
	{
		if (p == ptr && hdb_alloc(ptr) == 1)
		{
			set_hdb_alloc(ptr, 0);
			defragment(g_mem_tiny, zone_limit(g_mem_tiny), ptr);
			break ;
		}
		p = next_block(p);
	}
	if ((char *)p >= (char *)zone_limit(g_mem_tiny))
	{
		printf("Error: Trying to free pointer that was not allocated\n");
	}
}
