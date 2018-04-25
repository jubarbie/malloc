/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 18:04:48 by jubarbie         ###   ########.fr       */
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

# define TINY_SIZE 4000
# define SMALL_SIZE 40000
# define TINY_MAX 100
# define SMALL_MAX 4000

extern void	*g_mem_tiny;
extern void	*g_mem_small;
extern void	*g_mem_mediuml;
extern char	g_malloc_init;

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	show_alloc_mem();

#endif
