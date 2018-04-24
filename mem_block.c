/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:12:10 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/24 12:03:25 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

head_block  *hdb(void *ptr)
{
    return ((head_block *)ptr - 1);
}

foot_block  *ftb(void *ptr)
{
    return ((foot_block *)((char *)hdb(ptr) + hdb_size(ptr)) - 1);
}

void    set_ftb_size(void *ptr, size_t size)
{
    ftb(ptr)->size = size;
}

size_t  ftb_size(void *ptr)
{
    return (ftb(ptr)->size);
}

void    set_hdb(void *ptr, size_t size, char alloc)
{
    set_hdb_size(ptr, size);
    set_hdb_alloc(ptr, alloc);
}

void    set_hdb_alloc(void *ptr, char alloc)
{
    hdb(ptr)->allocated = alloc;
}

void    set_hdb_size(void *ptr, size_t size)
{
    hdb(ptr)->size = size;
}

char     hdb_alloc(void *ptr)
{
    return ((hdb(ptr))->allocated);
}

size_t   hdb_size(void *ptr)
{
    return ((hdb(ptr))->size);
}

void     *next_block(void *ptr)
{
    return ((char *)ptr + hdb_size(ptr));
}

size_t   block_size(size_t size)
{
    return (size + sizeof(head_block) + sizeof(foot_block));
}

size_t   payload_size(void *p)
{
    return (hdb_size(p) - sizeof(head_block) - sizeof(foot_block));
}
