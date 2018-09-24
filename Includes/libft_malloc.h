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
# include <sys/resource.h>
# include "libft.h"
# include "block.h"

# define TINY_SIZE 5440
# define TINY_MAX 512
# define SMALL_SIZE 20800
# define SMALL_MAX 2048

typedef struct	s_mem {
	void	*tiny;
	void	*small;
	void	*medium;
}				t_mem;

static pthread_mutex_t	g_mutex;
t_mem					g_mem;

extern void		*malloc(size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void 	*calloc(size_t nmemb, size_t size);
extern void		show_alloc_mem();

#endif
