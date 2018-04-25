/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:34:51 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 11:39:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_block(void *p)
{
	if (p == NULL)
	{
		printf("Attempt to print NULL block");
	}
	else
	{
		printf("[%zu|%d] %zu bytes [%zu] %p\n", hdb_size(p), hdb_alloc(p),
				payload_size(p), ftb_size(p), p);
	}
}

void			show_alloc_mem(void)
{
	void	*p;

	printf("----- Memory viewer -----\n");
	printf("TINY : %p - %lu bytes\n", g_mem_tiny, mem_zone_size(g_mem_tiny));
	p = g_mem_tiny;
	while ((char *)p < (char *)zone_limit(g_mem_tiny))
	{
		print_block(p);
		p = next_block(p);
	}
}
