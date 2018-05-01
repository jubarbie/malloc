/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/01 21:08:25 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem	g_mem = { .tiny = NULL, .small = NULL, .medium = NULL, .option = 0};

static char		get_options(void)
{
	if (getenv("MallocVerbose") != NULL)
		return (1);
	return (0);
}

static t_block	*malloc_in_mem(t_block *mem, size_t mem_size, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = mem;
	prev = block;
	while (block != NULL)
	{
		if (get_b_alloc(block) == 0 && size == get_b_size(block))
			return (set_b_alloc(block, 1));
		if (get_b_alloc(block) == 0 && block_size(size) <= get_b_size(block))
			return (split_block(block, size));
		prev = block;
		block = get_b_next(block);
	}
	if (block == NULL)
	{
		block = new_room(mem_size, prev, NULL);
		if (size == get_b_size(block))
			return (set_b_alloc(block, 1));
	}
	return (split_block(block, size));
}

static void		*init_mem(void **mem, size_t mem_size, size_t size)
{
	if (*mem == NULL)
		*mem = (void *)new_room(mem_size, NULL, NULL);
	return (payload(malloc_in_mem((t_block *)(*mem), mem_size, size)));
}

void			*ft_malloc(size_t size)
{
	g_mem.option = get_options();
	if (size == 0)
		return (NULL);
	if (g_mem.option == 1)
		ft_putendl("Mallocing");
	if (size <= TINY_MAX)
		return (init_mem(&(g_mem.tiny), TINY_SIZE, size));
	else if (size <= SMALL_MAX)
		return (init_mem(&(g_mem.small), SMALL_SIZE, size));
	else
		return (init_mem(&(g_mem.medium), size, size));
}
