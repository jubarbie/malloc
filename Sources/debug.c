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
	int fd;

	if (is_debug())
	{
		fd = open("malloc.log", O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd >= 0)
		{
			ft_putstr_fd("free: ", fd);
			print_addr(ptr, fd);
			ft_putchar_fd('\n', fd);
			close(fd);
		}
	}
}

void	debug_malloc(size_t size)
{
	int fd;

	if (is_debug())
	{
		fd = open("malloc.log", O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd >= 0)
		{
			ft_putstr_fd("malloc: ", fd);
			print_size(size, fd);
			ft_putstr_fd(" octets\t-> ", fd);
			close(fd);
		}
	}
}

void	debug_realloc(void *ptr, size_t size)
{
	int fd;

	if (is_debug())
	{
		fd = open("malloc.log", O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd >= 0)
		{
			ft_putstr_fd("realloc: ", fd);
			print_addr(ptr, fd);
			ft_putchar_fd(';', fd);
			print_size(size, fd);
			ft_putstr_fd(" octets\t-> ", fd);
			close(fd);
		}
	}
}

void	debug_calloc(size_t nb, size_t size)
{
	int fd;

	if (is_debug())
	{
		fd = open("malloc.log", O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd >= 0)
		{
			ft_putstr_fd("calloc: ", fd);
			print_size(nb, fd);
			ft_putstr_fd(" x ", fd);
			print_size(size, fd);
			ft_putstr_fd(" octets", fd);
			ft_putstr_fd("\t-> ", fd);
			close(fd);
		}
	}
}
