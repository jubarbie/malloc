/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:06:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 12:17:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# include <stdlib.h>
# include <sys/mman.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# define ALIGN(x,a) __ALIGN_MASK(x,(typeof(x))(a)-1)
# define __ALIGN_MASK(x,mask) (((x)+(mask))&~(mask))

typedef struct {
    size_t	size;
    size_t	max_free;
    void	*next;
} mem_zone;

extern size_t	g_page_size;

void			*create_mem_zone(size_t size);
mem_zone		*get_mem_zone(void *zone);
size_t			mem_zone_size(void *zone);
void			*zone_limit(void *zone);

#endif
