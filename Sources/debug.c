/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 20:31:17 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 21:32:41 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

void	debug_free(void *ptr)
{
	if (getenv("MALLOC_DEBUG") && !strcmp("y", getenv("MALLOC_DEBUG")))
	{
		ft_putstr("free: ");
		print_addr(ptr);
		ft_putchar('\n');
	}
}

void	debug_malloc(size_t size)
{
	if (getenv("MALLOC_DEBUG") && !strcmp("y", getenv("MALLOC_DEBUG")))
	{
		ft_putstr("malloc: ");
		print_size(size);
		ft_putstr(" octets\t-> ");
	}
}

void	debug_realloc(void *ptr, size_t size)
{
	if (getenv("MALLOC_DEBUG") && !strcmp("y", getenv("MALLOC_DEBUG")))
	{
		ft_putstr("realloc: ");
		print_addr(ptr);
		ft_putchar(';');
		print_size(size);
		ft_putstr(" octets\t-> ");
	}
}

void	debug_calloc(size_t nb, size_t size)
{
	if (getenv("MALLOC_DEBUG") && !strcmp("y", getenv("MALLOC_DEBUG")))
	{
		ft_putstr("calloc: ");
		print_size(nb);
		ft_putstr(" x ");
		print_size(size);
		ft_putstr(" octets");
		ft_putstr("\t-> ");
	}
}

void	debug_return(t_block *ptr)
{
	if (getenv("MALLOC_DEBUG") && !strcmp("y", getenv("MALLOC_DEBUG")))
	{
		if (ptr == NULL)
			ft_putstr("(null)\n");
		else
		{
			(is_b_first(ptr)) ? ft_putchar('.') : ft_putchar(' ');
			print_addr(ptr);
			ft_putstr(" [ ");
			print_size(ptr->size);
			ft_putstr(" ; ");
			print_addr(ptr->prev);
			ft_putstr(" ; ");
			print_addr(ptr->next);
			ft_putstr(" ]\n");
		}
	}
}

void	debug_new_room(size_t size)
{
	if (getenv("MALLOC_DEBUG") && !strcmp("y", getenv("MALLOC_DEBUG")))
	{
		ft_putstr("\n\tnew room: ");
		print_size(size);
		ft_putstr(" -> ");
	}
}

void	debug_print(char *str)
{
	if (str)
		ft_putstr(str);
	ft_putchar('\n');
}
