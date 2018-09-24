#include "block.h"
#include "libft_malloc.h"

t_block *attach_block(t_block *ptr, t_block *prev, t_block *next)
{
    if (ptr == NULL)
        return (NULL);
    ptr = set_b_prev(ptr, prev);
    ptr = set_b_next(ptr, next);
    if (prev != NULL)
		set_b_next(prev, ptr);
	if (next != NULL)
		set_b_prev(next, ptr);
    return (ptr);
}

size_t	count_alloc_blocks(t_block *ptr, size_t size)
{
	size_t	c;
	t_block	*p;
	size_t	asize;

	c = 0;
	p = ptr;
	asize = ALIGN(block_size(size), getpagesize());
	while (p != NULL && (char *)p < (char *)ptr + asize)
	{
		if (is_b_alloc(p))
			c++;
		p = get_b_next(p);
	}
	return (c);
}

t_block	*find_block_in_mem(t_block *mem, void *ptr)
{
	t_block *b;

	if (mem == NULL || ptr == NULL)
		return (NULL);
	b = mem;
	while (b != NULL)
	{
		if (payload_addr(b) == ptr)
			return (b);
		b = get_b_next(b);
	}
	return (NULL);
}

t_block	*find_block(void *ptr)
{
    t_block *b;

    if (ptr == NULL)
		return (NULL);
	b = find_block_in_mem(g_mem.tiny, ptr);
    if (b != NULL)
		return (b);
	b = find_block_in_mem(g_mem.small, ptr);
    if (b != NULL)
		return (b);
	b = find_block_in_mem(g_mem.medium, ptr);
    if (b != NULL)
		return (b);
	return (NULL);
}

char   b_cont(t_block *b1, t_block *b2)
{
    if (b1 == NULL || b2 == NULL)
        return (0);
    if (b1 > b2)
        return (0);
    if ((char *)payload_addr(b1) + get_b_size(b1) == (char *)b2)
        return (1);
    return (0);
}
