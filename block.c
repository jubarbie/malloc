/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:12:10 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 12:00:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

void		*next_block(void *ptr)
{
	return ((char *)ptr + hdb_size(ptr));
}

void		*prev_block(void *ptr)
{
	size_t		size;
	foot_block	*ft;

	ft = (foot_block *)hdb(ptr) - 1;
	size = ft->size - sizeof(head_block) - sizeof(foot_block);
	return ((char *)ft - size);
}

size_t		block_size(size_t size)
{
	return (size + sizeof(head_block) + sizeof(foot_block));
}

size_t		payload_size(void *p)
{
	return (hdb_size(p) - sizeof(head_block) - sizeof(foot_block));
}
