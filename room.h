/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:06:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 12:22:41 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# include <stdlib.h>
# include <sys/mman.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define ALIGN(x,a) __ALIGN_MASK(x,(typeof(x))(a)-1)
# define __ALIGN_MASK(x,mask) (((x)+(mask))&~(mask))

# pragma pack (1)

typedef struct {
	size_t	size;
	size_t	max_free;
	void	*next;
}	t_hd_room;

void		*new_room(size_t size);
t_hd_room	*get_hd_room(void *room);
size_t		room_size(void *room);
void		*room_limit(void *room);
void		*next_room(void *room);

#endif
