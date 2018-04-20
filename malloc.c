/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/20 16:44:57 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *mem_tiny;
void    *mem_small;
char    malloc_init = 0;

static void     *next_block(void *p)
{
    return ((char *)p + HDB_SIZE(p));
}

static size_t   get_block_size(size_t size)
{
    return (ALIGN(size, PAGE_SIZE) + HDB_SIZE_ALIGN);
}

static void    *init_malloc()
{
    size_t  size;
    
    size = get_block_size(TINY_SIZE);
    mem_tiny = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem_tiny == (void *) -1)
    {
        printf("Could not map tiny mem: %s\n", strerror(errno));
        return NULL;
    }
    mem_tiny = (char *)mem_tiny + HDB_SIZE_ALIGN;
    HDB_SIZE(mem_tiny) = size;
    HDB_ALLOC(mem_tiny) = 0;

    malloc_init = 1;
    return mem_tiny;
}

static void     *malloc_in(void *first, size_t size)
{
    void    *p;
    void    *new;
    size_t  s;

    p = first;
    s = get_block_size(size);
    while ((HDB_ALLOC(p) == 1 || (HDB_ALLOC(p) == 0 && HDB_SIZE(p) < s)) && (char *)p < (char *)first + get_block_size(TINY_SIZE))
    {
        p = next_block(p);
    }
    if ((char *)p >= (char *)first + get_block_size(TINY_SIZE)) {
        return NULL;
    }
    new = (char *)p + s;
    HDB_SIZE(new) = HDB_SIZE(p) - s;
    HDB_ALLOC(new) = 0;
    HDB_SIZE(p) = s;
    HDB_ALLOC(p) = 1;
    return p;
}

static void     print_block(void *p)
{
    if (p == NULL)
    {
        printf("Attempt to print NULL block");
    }
    else
    {
        printf("[%zu|%d] %p\n", HDB_SIZE(p), HDB_ALLOC(p), p);
    }
}

void            *ft_malloc(size_t size)
{  
    void    *p;

    if (malloc_init == 0)
    {
        p = init_malloc();
        if (p == (void *)-1) return p;
    }
    return malloc_in(mem_tiny, size);
}

void    show_alloc_mem()
{
    void    *p;

    printf("TINY : %p\n", mem_tiny);
    p = mem_tiny;
    while((char *)p < (char *)mem_tiny + get_block_size(TINY_SIZE))
    {
        print_block(p);
        p = next_block(p);
    }
}
