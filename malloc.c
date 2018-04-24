/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:36:03 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/24 16:15:02 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *mem_tiny;
void    *mem_small;
size_t  tiny_size;
size_t  small_size;
size_t  page_size;
char    malloc_init = 0;

static void    *init_malloc()
{
    page_size = sysconf(_SC_PAGE_SIZE);
    tiny_size = (ALIGN(block_size(TINY_SIZE), page_size));
    mem_tiny = mmap(NULL, tiny_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem_tiny == (void *) -1)
    {
        printf("Could not map tiny mem: %s\n", strerror(errno));
        return NULL;
    }
    mem_tiny = (head_block *)mem_tiny + 1;
    set_hdb(mem_tiny, tiny_size, 0);
    set_ftb_size(mem_tiny, tiny_size);

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
    while ((hdb_alloc(p) == 1 || (hdb_alloc(p) == 0 && (blk_sz > payload_size(p)))) && (char *)p + blk_sz < (char *)first + tiny_size)
    {
        p = next_block(p);
    }
    if ((char *)p + blk_sz > (char *)first + tiny_size) {
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
    return malloc_in(mem_tiny, size);
}

void    defragment(void *min, void *max, void *ptr)
{
    size_t  size;
   

    printf("b: %p\n", ptr);
    while (prev_block(ptr) >= min && hdb_alloc(prev_block(ptr)) == 0)
    {
        ptr = prev_block(ptr);
        if (ptr == min)
        {
            break ;
        }
    }
    printf("%p\n", ptr);
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
    while((char *)p < (char *)mem_tiny + tiny_size)
    {
        if (p == ptr)
        {
            set_hdb_alloc(ptr, 0);
            defragment(mem_tiny, (void *)((char *)mem_tiny + tiny_size), ptr);
            break;
        }
        p = next_block(p);
    }
    if ((char *)p >= (char *)mem_tiny + tiny_size)
    {
        printf("Error: Trying to free pointer that was not allocated\n");
    }
}

void    show_alloc_mem()
{
    void    *p;

    printf("------- Memory viewer -------\nTINY : %p - %lu bytes\n", mem_tiny, tiny_size);
    p = mem_tiny;
    while((char *)p < (char *)mem_tiny + tiny_size)
    {
        print_block(p);
        p = next_block(p);
    }
}
