/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:00:26 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 19:46:32 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define ALIGN(x,a) __ALIGN_MASK(x,(typeof(x))(a)-1)
# define __ALIGN_MASK(x,mask) (((x)+(mask))&~(mask))

# pragma pack(1)

typedef struct s_block {
	size_t			size;
	struct s_block	*next;
	struct s_block	*prev;
	char			allocated;
}	t_block;

size_t		block_size(size_t size);
char		get_b_alloc(t_block *ptr);
size_t		get_b_size(t_block *ptr);
t_block		*new_room(size_t size, t_block *prev, t_block *next);
t_block		*set_b_size(t_block *ptr, size_t size);
t_block		*set_b_next(t_block *ptr, t_block *next);
t_block		*set_b_prev(t_block *ptr, t_block *prev);
t_block		*set_b_alloc(t_block *ptr, char alloc);
t_block		*set_b(t_block *ptr, size_t size, char alloc);
t_block		*get_b_next(t_block *ptr);
t_block		*get_b_prev(t_block *ptr);
size_t		count_alloc_blocks(t_block *ptr, size_t size);
t_block		*split_block(t_block *ptr, size_t size);
void		*payload(t_block *ptr);

#endif
