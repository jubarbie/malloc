/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/20 17:25:32 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>

# define ALIGN(x,a) __ALIGN_MASK(x,(typeof(x))(a)-1)
# define __ALIGN_MASK(x,mask) (((x)+(mask))&~(mask))

# define PAGE_SIZE sysconf(_SC_PAGE_SIZE)
# define TINY_SIZE 40000
# define SMALL_SIZE 40000
# define HDB(p) ((head_block *)p - 1)
# define HDB_SIZE(p) HDB(p)->size
# define HDB_ALLOC(p) HDB(p)->allocated 

typedef struct {
    size_t  size;
    char    allocated;
} head_block;

extern void    *mem_tiny;
extern void    *mem_small;
extern size_t   tiny_size;
extern size_t   small_size;
extern char     malloc_init;

void    *ft_malloc(size_t size);
void    ft_free(void *ptr);
void    show_alloc_mem();

#endif
