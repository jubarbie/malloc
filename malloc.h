/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/20 15:39:37 by jubarbie         ###   ########.fr       */
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
# define HDB(p) ((head_block *)((char *)p - HDB_SIZE_ALIGN))
# define HDB_SIZE(p) HDB(p)->size
# define HDB_ALLOC(p) HDB(p)->allocated 
# define HDB_SIZE_ALIGN ALIGN(sizeof(head_block), PAGE_SIZE)

typedef struct {
    size_t  size;
    char    allocated;
} head_block;

extern void    *mem_tiny;
extern void    *mem_small;
extern char     malloc_init;

void    *ft_malloc(size_t size);
void    show_alloc_mem();

#endif
