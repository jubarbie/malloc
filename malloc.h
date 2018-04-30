/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 19:18:32 by jubarbie         ###   ########.fr       */
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

# define TINY_SIZE 20000
# define TINY_MAX 2000
# define SMALL_SIZE 100000
# define SMALL_MAX 10000

# pragma pack(1)

typedef struct {
	void	*tiny;
	void	*small;
	void	*medium;
} t_mem;

extern t_mem	g_mem;

extern void	*ft_malloc(size_t size);
extern void	ft_free(void *ptr);
extern void	show_alloc_mem();

#endif
