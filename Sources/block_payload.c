/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_payload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:45:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 19:34:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

void	*payload_addr(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	return ((void *)(ptr + 1));
}

char	is_splittable(t_block *block, size_t size)
{
	if (block == NULL)
		return (0);
	return (get_b_size(block) >= size + block_size(align_16(1)));
}

char	is_fitting(t_block *block, size_t size)
{
	if (block == NULL)
		return (0);
	return (get_b_size(block) >= size &&
			get_b_size(block) < size + block_size(align_16(1)));
}
