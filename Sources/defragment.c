#include "libft_malloc.h"

t_block *defrag_next(t_block *b)
{
	t_block	*tmp;

    if (b == NULL || is_b_alloc(b))
        return (NULL);
	tmp = b;
	while (get_b_next(tmp) && !is_b_alloc(get_b_next(tmp)))
		tmp = fusion_blocks(tmp, get_b_next(tmp));
    return (tmp);
}

t_block *defrag_prev(t_block *b)
{
	t_block	*tmp;

    if (b == NULL || is_b_alloc(b))
        return (NULL);
	tmp = b;
    while (get_b_prev(tmp) && !is_b_alloc(get_b_prev(tmp)))
		tmp = fusion_blocks(get_b_prev(tmp), tmp);
    return (tmp);
}
