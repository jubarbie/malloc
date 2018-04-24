/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:18:56 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/24 11:59:47 by jubarbie         ###   ########.fr       */
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

# define TINY_SIZE 40000
# define SMALL_SIZE 40000
# define HDB(p) ((head_block *)p - 1)
# define HDB_SIZE(p) HDB(p)->size
# define HDB_ALLOC(p) HDB(p)->allocated 

typedef struct {
    size_t  size;
    char    allocated;
} head_block;

typedef struct {
    size_t  size;
} foot_block;

extern void    *mem_tiny;
extern void    *mem_small;
extern size_t   tiny_size;
extern size_t   small_size;
extern char     malloc_init;
extern size_t   page_size;

head_block   *hdb(void *ptr);
char    hdb_alloc(void *ptr);
size_t  hdb_size(void *ptr);
void    set_hdb_size(void *ptr, size_t size);
void    set_hdb_alloc(void *ptr, char alloc);
void    set_hdb(void *ptr, size_t size, char alloc);
foot_block   *ftb(void *ptr);
void    set_ftb_size(void *ptr, size_t size);
size_t  ftb_size(void *ptr);
void    *next_block(void *ptr);
size_t  block_size(size_t size);
size_t  payload_size(void *ptr);
void    *ft_malloc(size_t size);
void    ft_free(void *ptr);
void    show_alloc_mem();

#endif
