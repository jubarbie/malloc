/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/20 18:16:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *mem_tiny;
void    *mem_small;
size_t  tiny_size;
size_t  small_size;
char    malloc_init = 0;

static void     *next_block(void *p)
{
    return ((char *)p + HDB_SIZE(p));
}

static size_t   block_size(size_t size)
{
    return (size + sizeof(head_block));
}

static size_t   payload_size(void *p)
{
    return (HDB_SIZE(p) - sizeof(head_block));
}

static void    *init_malloc()
{
    tiny_size = (ALIGN(block_size(TINY_SIZE), PAGE_SIZE));
    mem_tiny = mmap(NULL, tiny_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem_tiny == (void *) -1)
    {
        printf("Could not map tiny mem: %s\n", strerror(errno));
        return NULL;
    }
    mem_tiny = (head_block *)mem_tiny + 1;
    HDB_SIZE(mem_tiny) = tiny_size;
    HDB_ALLOC(mem_tiny) = 0;

    malloc_init = 1;
    return mem_tiny;
}

static void     *malloc_in(void *first, size_t size)
{
    void    *p;
    void    *new;
    size_t  blk_sz;

    p = first;
    blk_sz = block_size(size);
    while ((HDB_ALLOC(p) == 1 || (HDB_ALLOC(p) == 0 && (blk_sz > payload_size(p)))) && (char *)p + blk_sz < (char *)first + tiny_size)
    {
        p = next_block(p);
    }
    if ((char *)p + blk_sz > (char *)first + tiny_size) {
        return NULL;
    }
    if (blk_sz == HDB_SIZE(p)) {
        HDB_ALLOC(p) = 1;
        return p;
    }
    new = (char *)p + blk_sz;
    HDB_SIZE(new) = HDB_SIZE(p) - blk_sz;
    HDB_ALLOC(new) = 0;
    HDB_SIZE(p) = blk_sz;
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

void    ft_free(void *ptr)
{
    if (ptr != NULL)
    {
        HDB_ALLOC(ptr) = 0;
    }
}

void    show_alloc_mem()
{
    void    *p;

    printf("TINY : %p - %lu bytes\n", mem_tiny, tiny_size);
    p = mem_tiny;
    while((char *)p < (char *)mem_tiny + tiny_size)
    {
        print_block(p);
        p = next_block(p);
    }
}
