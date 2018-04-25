/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:45:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 14:32:28 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

t_hdb	*hdb(void *ptr)
{
	return ((t_hdb *)ptr - 1);
}

void	set_hdb(void *ptr, size_t size, char alloc)
{
	set_hdb_size(ptr, size);
	set_hdb_alloc(ptr, alloc);
}

void	set_hdb_alloc(void *ptr, char alloc)
{
	hdb(ptr)->allocated = alloc;
}

void	set_hdb_size(void *ptr, size_t size)
{
	hdb(ptr)->size = size;
}

char	hdb_alloc(void *ptr)
{
	return ((hdb(ptr))->allocated);
}

size_t	hdb_size(void *ptr)
{
	return ((hdb(ptr))->size);
}
