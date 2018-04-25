/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:00:26 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 14:47:13 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <stdlib.h>

typedef struct {
	size_t	size;
	char	allocated;
}	t_hdb;

typedef struct {
	size_t	size;
}	t_ftb;

t_hdb		*hdb(void *ptr);
char		hdb_alloc(void *ptr);
size_t		hdb_size(void *ptr);
void		set_hdb_size(void *ptr, size_t size);
void		set_hdb_alloc(void *ptr, char alloc);
void		set_hdb(void *ptr, size_t size, char alloc);
t_ftb		*ftb(void *ptr);
void		set_ftb_size(void *ptr, size_t size);
size_t		ftb_size(void *ptr);
void		*next_block(void *ptr);
void		*prev_block(void *ptr);
void		split_block(void *ptr, size_t size);
size_t		block_size(size_t size);
size_t		payload_size(void *ptr);

#endif
