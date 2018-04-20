/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:55:02 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/20 17:34:17 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
    void *p1 = ft_malloc(2);
    void *p2 = ft_malloc(2);
    void *p3 = ft_malloc(sizeof(char) * 8000);
    if (p1 == NULL || p2 == NULL || p3 == NULL)
    {
        printf("Error in malloc");
    }
    ft_free(p2);
    show_alloc_mem();
    p2 = ft_malloc(3);
    show_alloc_mem();
    return (0);
}
