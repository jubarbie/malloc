/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/24 18:52:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *mem_tiny;
void    *mem_small;
size_t  page_size;
char    malloc_init = 0;

static size_t   zone_size(size_t size)
{
    return (block_size(size) + sizeof(mem_zone));
}

static void     *create_mem_zone(size_t size)
{
    size_t  zsize;
    void    *p;
    
    zsize = (ALIGN(zone_size(size), page_size));
    p = mmap(NULL, zsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (p == NULL)
    {
        printf("Could not map %zu bytes: %s\n", zsize, strerror(errno));
        return NULL;
    }
    ((mem_zone *)p)->size = zsize;
    ((mem_zone *)p)->next = NULL;
    p = (char *)p + sizeof(mem_zone) + sizeof(head_block);
    set_hdb(p, zsize - sizeof(mem_zone), 0);
    set_ftb_size(p, zsize - sizeof(mem_zone));
    return p;
}

static void     *add_mem_zone(void *first, size_t size)
{
    mem_zone    *p;

    if (first == NULL)
    {
        first = create_mem_zone(size);
        return first;
    }
    p = (mem_zone *)first;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = create_mem_zone(size);
    return p->next;
}

static void    *init_malloc()
{
    page_size = sysconf(_SC_PAGE_SIZE);
    mem_tiny = NULL;
    mem_tiny = add_mem_zone(mem_tiny, TINY_SIZE);
    malloc_init = 1;
    return mem_tiny;
}

static mem_zone *get_mem_zone(void *zone)
{
    return (mem_zone *)((char *)zone - sizeof(head_block) - sizeof(mem_zone));
}

static size_t   mem_zone_size(void *zone)
{
    return (get_mem_zone(zone)->size);
}

static void     *zone_limit(void *zone)
{
    return (void *)((char *)zone + mem_zone_size(zone) - sizeof(mem_zone) - sizeof(head_block));
}

static void     *malloc_in_zone(void *zone, size_t size)
{
    void    *p;
    void    *new;
    size_t  blk_sz;

    p = zone;
    blk_sz = block_size(size);
    while ((hdb_alloc(p) == 1 || (hdb_alloc(p) == 0 && (blk_sz > payload_size(p)))) && (char *)p + blk_sz < (char *)zone_limit(zone))
    {
        p = next_block(p);
    }
    if ((char *)p + blk_sz > (char *)zone_limit(zone)) {
        return NULL;
    }
    if (blk_sz == hdb_size(p)) {
        set_hdb_alloc(p, 1);
        return p;
    }
    new = (char *)p + blk_sz;
    set_hdb(new, hdb_size(p) - blk_sz, 0);
    set_ftb_size(new, hdb_size(p) - blk_sz);
    set_hdb(p, blk_sz, 1);
    set_ftb_size(p, blk_sz);
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
        printf("[%zu|%d] %zu bytes [%zu] %p\n", hdb_size(p), hdb_alloc(p), payload_size(p), ftb_size(p), p);
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
    return malloc_in_zone(mem_tiny, size);
}

void    defragment(void *min, void *max, void *ptr)
{
    size_t  size;

    while (prev_block(ptr) >= min && hdb_alloc(prev_block(ptr)) == 0)
    {
        ptr = prev_block(ptr);
        if (ptr == min)
        {
            break ;
        }
    }
    while (next_block(ptr) < max && hdb_alloc(next_block(ptr)) == 0)
    {
        size =  hdb_size(ptr) + hdb_size(next_block(ptr));
        set_hdb(ptr, size, 0);
        set_ftb_size(ptr, size);
    } 
}

void    ft_free(void *ptr)
{
    void *p;

    p = mem_tiny;
    while((char *)p < (char *)zone_limit(mem_tiny))
    {
        if (p == ptr && hdb_alloc(ptr) == 1)
        {
            set_hdb_alloc(ptr, 0);
            defragment(mem_tiny, zone_limit(mem_tiny), ptr);
            break;
        }
        p = next_block(p);
    }
    if ((char *)p >= (char *)zone_limit(mem_tiny))
    {
        printf("Error: Trying to free pointer that was not allocated\n");
    }
}

void    show_alloc_mem()
{
    void    *p;

    printf("------- Memory viewer -------\nTINY : %p - %lu bytes\n", mem_tiny, mem_zone_size(mem_tiny));
    p = mem_tiny;
    while((char *)p < (char *)zone_limit(mem_tiny))
    {
        print_block(p);
        p = next_block(p);
    }
}
