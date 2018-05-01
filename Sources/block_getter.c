/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:45:27 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/01 12:21:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

char	get_b_alloc(t_block *ptr)
{
	if (ptr == NULL)
		return (-1);
	return (ptr->allocated);
}

size_t	get_b_size(t_block *ptr)
{
	if (ptr == NULL)
		return (0);
	return (ptr->size);
}

t_block	*get_b_next(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	return (ptr->next);
}

t_block	*get_b_prev(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	return (ptr->prev);
}
