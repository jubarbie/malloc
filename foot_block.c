/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foot_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:44:21 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 13:37:04 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

t_ftb	*ftb(void *ptr)
{
	return ((t_ftb *)((char *)hdb(ptr) + hdb_size(ptr)) - 1);
}

void	set_ftb_size(void *ptr, size_t size)
{
	ftb(ptr)->size = size;
}

size_t	ftb_size(void *ptr)
{
	return (ftb(ptr)->size);
}
