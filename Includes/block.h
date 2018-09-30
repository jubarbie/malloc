/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:00:26 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 21:31:22 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_block {
	size_t			size;
	struct s_block	*next;
	struct s_block	*prev;
	char			status;
}				t_block;

/*
** Block setters
*/
t_block			*set_b_size(t_block *ptr, size_t size);
t_block			*set_b_next(t_block *ptr, t_block *next);
t_block			*set_b_prev(t_block *ptr, t_block *prev);
t_block			*set_b_all(t_block *ptr, size_t s, char first, char alloc);
/*
** Block getters
*/
char			get_b_status(t_block *ptr);
size_t			get_b_size(t_block *ptr);
t_block			*get_b_next(t_block *ptr);
t_block			*get_b_prev(t_block *ptr);
/*
** Block status
*/
t_block			*set_b_first(t_block *ptr);
t_block			*set_b_alloc(t_block *ptr);
t_block			*set_b_free(t_block *ptr);
char			is_b_first(t_block *ptr);
char			is_b_alloc(t_block *ptr);
/*
** Block helper
*/
t_block			*init_block(void *ptr);
void			*payload_addr(t_block *ptr);
size_t			block_size(size_t size);
t_block			*split_block(t_block *ptr, size_t size);
t_block			*fusion_blocks(t_block *block, t_block *next);
char			is_splittable(t_block *block, size_t size);
char			is_fitting(t_block *block, size_t size);
/*
** Block list
*/
t_block			*attach_block(t_block *ptr, t_block *prev, t_block *next);
size_t			count_alloc_blocks(t_block *ptr, size_t size);
t_block			*find_block(void *ptr);
t_block			*find_block_in_mem(t_block *mem, void *ptr);
char			b_cont(t_block *b1, t_block *b2);
/*
** Malloc
*/
t_block			*dispatch_alloc(size_t size);
t_block			*new_room(size_t size, t_block *prev, t_block *next);
/*
** Free
*/
void			pthsafe_free(void *ptr);
t_block			*defragment(t_block *ptr);
/*
** Defragment
*/
t_block			*defrag_next(t_block *b);
t_block			*defrag_prev(t_block *b);
/*
** Show allocation memory
*/
void			print_addr(void *ptr, int fd);
void			print_size(size_t size, int fd);
void			print_hex_dump(t_block *b);
/*
** Align
*/
size_t			align_16(size_t size);
size_t			align_page(size_t size);
/*
** Options
*/
char			has_env(const char *var, const char *value);
/*
** Debug
*/
void			debug_free(void *ptr);
void			debug_realloc(void *ptr, size_t size);
void			debug_calloc(size_t nb, size_t size);
void			debug_malloc(size_t size);
void			debug_new_room(size_t size);
void			debug_block(t_block *ptr);
void			debug_print(char *str);

#endif
