/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:12:10 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 15:06:07 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

void	split_block(void *start, size_t size)
{
	void	*new;

	new = (char *)start + size;
	set_hdb(new, hdb_size(start) - size, 0);
	set_ftb_size(new, hdb_size(start) - size);
	set_hdb(start, size, 1);
	set_ftb_size(start, size);
}

void	*next_block(void *ptr)
{
	return ((char *)ptr + hdb_size(ptr));
}

void	*prev_block(void *ptr)
{
	size_t	size;
	t_ftb	*ft;

	ft = (t_ftb *)hdb(ptr) - 1;
	size = ft->size - sizeof(t_hdb) - sizeof(t_ftb);
	return ((char *)ft - size);
}

size_t	block_size(size_t size)
{
	return (size + sizeof(t_hdb) + sizeof(t_ftb));
}

size_t	payload_size(void *p)
{
	return (hdb_size(p) - sizeof(t_hdb) - sizeof(t_ftb));
}
