/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 12:17:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*g_mem_tiny;
void	*g_mem_small;
size_t	g_page_size;
char	g_malloc_init = 0;

static void		*add_mem_zone(void *first, size_t size)
{
	mem_zone	*p;

	if (first == NULL)
	{
		first = create_mem_zone(size);
		return (first);
	}
	p = (mem_zone *)first;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = create_mem_zone(size);
	return (p->next);
}

static void		*init_malloc(void)
{
	g_page_size = getpagesize(); ;
	g_mem_tiny = NULL;
	g_mem_tiny = add_mem_zone(g_mem_tiny, TINY_SIZE);
	g_malloc_init = 1;
	return (g_mem_tiny);
}

static void		*malloc_in_zone(void *zone, size_t size)
{
	void	*p;
	void	*new;
	size_t	blk_sz;

	p = zone;
	blk_sz = block_size(size);
	while ((hdb_alloc(p) == 1 || (hdb_alloc(p) == 0 && (blk_sz >
	payload_size(p)))) && (char *)p + blk_sz < (char *)zone_limit(zone))
	{
		p = next_block(p);
	}
	if ((char *)p + blk_sz > (char *)zone_limit(zone))
	{
		return (NULL);
	}
	if (blk_sz == hdb_size(p))
	{
		set_hdb_alloc(p, 1);
		return (p);
	}
	new = (char *)p + blk_sz;
	set_hdb(new, hdb_size(p) - blk_sz, 0);
	set_ftb_size(new, hdb_size(p) - blk_sz);
	set_hdb(p, blk_sz, 1);
	set_ftb_size(p, blk_sz);
	return (p);
}

void			*ft_malloc(size_t size)
{
	void	*p;

	if (g_malloc_init == 0)
	{
		p = init_malloc();
		if (p == (void *)-1)
		{
			return (p);
		}
	}
	return (malloc_in_zone(g_mem_tiny, size));
}
