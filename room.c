/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:24:17 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 12:11:39 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"
#include "block.h"

size_t		g_page_size;

void		*create_mem_zone(size_t size)
{
	void	*p;

	size = block_size(size) + sizeof(mem_zone);
	size = (ALIGN(size, g_page_size));
	p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == NULL)
	{
		printf("Could not map %zu bytes: %s\n", size, strerror(errno));
		return (NULL);
	}
	((mem_zone *)p)->size = size;
	((mem_zone *)p)->next = NULL;
	p = (char *)p + sizeof(mem_zone) + sizeof(head_block);
	set_hdb(p, size - sizeof(mem_zone), 0);
	set_ftb_size(p, size - sizeof(mem_zone));
	return (p);
}

mem_zone	*get_mem_zone(void *zone)
{
	return ((mem_zone *)((char *)zone - sizeof(head_block) - sizeof(mem_zone)));
}

size_t		mem_zone_size(void *zone)
{
	return (get_mem_zone(zone)->size);
}

void		*zone_limit(void *zone)
{
	size_t	meta_size;

	meta_size = sizeof(mem_zone) + sizeof(head_block);
	return ((void *)((char *)zone + mem_zone_size(zone) - meta_size));
}
