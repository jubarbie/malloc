/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/28 18:47:29 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include "block.h"
# include "room.h"

# define TINY_SIZE 10000
# define TINY_MAX 1000
# define SMALL_SIZE 100000
# define SMALL_MAX 10000

extern void	*g_mem_tiny;
extern void	*g_mem_small;
extern void	*g_mem_medium;
extern char	g_malloc_init;

extern void	*ft_malloc(size_t size);
extern void	ft_free(void *ptr);
extern void	show_alloc_mem();

#endif
