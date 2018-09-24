#include "block.h"

t_block *init_block(void *ptr)
{
    t_block *b;

	if (ptr == NULL)
		return (NULL);
    b = (t_block *)ptr;
    b->size = 0;
	b->next = NULL;
	b->prev = NULL;
	b->status = 0;
    return (b);
}

void    *payload_addr(t_block *ptr)
{
	if (ptr == NULL)
		return (NULL);
	return ((void *)(ptr + 1));
}

size_t  block_size(size_t size)
{
	return (size + sizeof(t_block));
}

t_block	*split_block(t_block *ptr, size_t size)
{
	t_block	*new;

	if (ptr == NULL || (block_size(size) > get_b_size(ptr)))
		return (NULL);
	else if (size == get_b_size(ptr) || block_size(size) == get_b_size(ptr))
		return (set_b_alloc(ptr));
	new = init_block((char *)payload_addr(ptr) + size);
	set_b_all(new, get_b_size(ptr) - block_size(size), 0, 0);
	set_b_size(ptr, size);
	set_b_alloc(ptr);
	attach_block(new, ptr, get_b_next(ptr));
	return (ptr);
}

t_block	*fusion_blocks(t_block *block, t_block *next)
{
	if (!b_cont(block, next) || is_b_first(next))
		return (NULL);
	set_b_size(block, block_size(get_b_size(next)) + get_b_size(block));
	attach_block(block, get_b_prev(block), get_b_next(next));
	return (block);
}
