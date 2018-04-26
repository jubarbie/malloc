/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:24:17 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/26 16:29:00 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"
#include "block.h"

size_t		g_page_size;

void		*new_room(size_t size)
{
	void	*p;

	size = block_size(size) + sizeof(t_hd_room);
	size = (ALIGN(size, g_page_size));
	p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	printf("Mapping: %p - %zu\n", p, size);
	if (p == NULL)
	{
		printf("Could not map %zu bytes: %s\n", size, strerror(errno));
		return (NULL);
	}
	((t_hd_room *)p)->size = size;
	((t_hd_room *)p)->next = NULL;
	p = (char *)p + sizeof(t_hd_room) + sizeof(t_hdb);
	set_hdb(p, size - sizeof(t_hd_room), 0);
	set_ftb_size(p, size - sizeof(t_hd_room));
	return (p);
}

t_hd_room	*get_hd_room(void *room)
{
	size_t	meta_size;

	meta_size = sizeof(t_hd_room) + sizeof(t_hdb);
	return ((t_hd_room *)((char *)room - meta_size));
}

size_t		room_size(void *room)
{
	return (get_hd_room(room)->size);
}

void		*room_limit(void *room)
{
	size_t	meta_size;

	meta_size = sizeof(t_hd_room) + sizeof(t_hdb);
	return ((void *)((char *)room + room_size(room) - meta_size));
}

void		*next_room(void *room)
{
	return (get_hd_room(room)->next);
}
