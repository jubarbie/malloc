/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/24 19:56:07 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <sys/resource.h>
# include "libft.h"
# include "block.h"

# define TINY 128
# define SMALL 2048

typedef struct	s_mem {
	void	*tiny;
	void	*small;
	void	*medium;
	char	options;
}				t_mem;

extern t_mem			g_mem;
static pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

extern void		*malloc(size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		*calloc(size_t nmemb, size_t size);
extern void		show_alloc_mem();

#endif
