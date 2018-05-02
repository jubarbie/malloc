/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 16:49:36 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"
# include "block.h"

# define TINY_SIZE 10240
# define TINY_MAX 1024
# define SMALL_SIZE 102400
# define SMALL_MAX 10240

typedef struct	s_mem {
	void	*tiny;
	void	*small;
	void	*medium;
	char	option;
}				t_mem;

extern	t_mem	g_mem;

extern void		*malloc(size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		show_alloc_mem();

#endif
