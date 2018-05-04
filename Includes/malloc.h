/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 20:00:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
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

t_mem			g_mem;
pthread_mutex_t	g_mutex;

extern void		*malloc(size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		show_alloc_mem();

#endif
