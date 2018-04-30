/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:45:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 15:55:21 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

char	get_b_alloc(t_block *ptr)
{
	return (ptr->allocated);
}

size_t	get_b_size(t_block *ptr)
{
	return (ptr->size);
}

t_block	*get_b_next(t_block *ptr)
{
	return (ptr->next);
}

t_block	*get_b_prev(t_block *ptr)
{
	return (ptr->prev);
}
