/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 12:04:32 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/29 12:04:35 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

t_block	*set_b_first(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	ptr->status |= (1 << 2);
	return (ptr);
}

t_block	*set_b_alloc(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	ptr->status |= (1 << 3);
	return (ptr);
}

t_block	*set_b_free(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	ptr->status &= ~(1 << 3);
	return (ptr);
}

char	is_b_first(t_block *ptr)
{
	if (ptr == NULL)
		return (0);
	return (ptr->status & (1 << 2));
}

char	is_b_alloc(t_block *ptr)
{
	if (ptr == NULL)
		return (0);
	return (ptr->status & (1 << 3));
}
