/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:00:26 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 12:31:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <stdlib.h>

# pragma pack(1)

typedef struct {
	size_t	size;
	char	allocated;
}	t_hdb;

t_hdb		*hdb(void *ptr);
char		hdb_alloc(void *ptr);
size_t		hdb_size(void *ptr);
size_t		count_alloc_blocks(void *ptr);
void		set_hdb_size(void *ptr, size_t size);
void		set_hdb_alloc(void *ptr, char alloc);
void		set_hdb(void *ptr, size_t size, char alloc);
size_t		*ftb(void *ptr);
void		set_ftb_size(void *ptr, size_t size);
size_t		ftb_size(void *ptr);
void		*next_block(void *ptr);
void		*prev_block(void *ptr);
void		split_block(void *ptr, size_t size);
size_t		block_size(size_t size);
size_t		payload_size(void *ptr);

#endif
