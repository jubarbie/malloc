/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 11:50:07 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/29 11:50:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft_malloc.h"

size_t	align_16(size_t size)
{
	return (((size - 1) | 15) + 1);
}

size_t	align_page(size_t size)
{
	return (((size - 1) | (getpagesize() - 1)) + 1);
}
