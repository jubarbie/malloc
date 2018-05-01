/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/01 21:15:43 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
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

extern void		*ft_malloc(size_t size);
extern void		ft_free(void *ptr);
extern void		*ft_realloc(void *ptr, size_t size);
extern void		show_alloc_mem();

#endif
