/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 10:52:59 by jubarbie          #+#    #+#             */
/*   Updated: 2018/10/01 10:53:03 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block.h"

void	debug_block(t_block *ptr)
{
	int fd;

	if (is_debug())
	{
		fd = open("malloc.log", O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd >= 0)
		{
			if (ptr == NULL)
				ft_putstr_fd("(null)\n", fd);
			else
			{
				(is_b_first(ptr)) ? ft_putchar_fd('.', fd) :
												ft_putchar_fd(' ', fd);
				print_addr(ptr, fd);
				ft_putstr_fd(" [ ", fd);
				print_size(ptr->size, fd);
				ft_putstr_fd(" ; ", fd);
				print_addr(ptr->prev, fd);
				ft_putstr_fd(" ; ", fd);
				print_addr(ptr->next, fd);
				ft_putstr_fd(" ]\n", fd);
			}
			close(fd);
		}
	}
}

void	debug_print(char *str)
{
	int fd;

	if (str && is_debug())
	{
		fd = open("malloc.log", O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd >= 0)
		{
			ft_putstr_fd(str, fd);
			ft_putchar_fd('\n', fd);
			close(fd);
		}
	}
}
