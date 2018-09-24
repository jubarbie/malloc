#include "libft_malloc.h"

static char is_overflowing(size_t n1, size_t n2, size_t res)
{
    if (n1 != 0 && res / n1 != n2)
        return (1);
    return (0);
}
void        *calloc(size_t nmemb, size_t size)
{
    t_block *block;
    size_t  alsize;

    alsize = nmemb * size;
    if (size == 0 || nmemb == 0)
        return (NULL);
    if (is_overflowing(nmemb, size, alsize))
        return (NULL);
    alsize = align_16(alsize);
    pthread_mutex_lock(&g_mutex);
	block = dispatch_alloc(alsize);
    ft_bzero(payload_addr(block), alsize);
	pthread_mutex_unlock(&g_mutex);
    return (payload_addr(block));
}
