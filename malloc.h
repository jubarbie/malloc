/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 19:33:53 by jubarbie         ###   ########.fr       */
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

# define TINY_SIZE 4000
# define TINY_MAX 1024
# define SMALL_SIZE 102400
# define SMALL_MAX 10240

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
