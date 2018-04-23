/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:55:02 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/23 18:14:18 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
    void *p1 = ft_malloc(2);
    void *p2 = ft_malloc(23 * sizeof(int));
    void *p3 = ft_malloc(sizeof(char) * 8124);
    void *p4 = ft_malloc(sizeof(char) * 80);
    void *p5 = ft_malloc(sizeof(char) * 450);
    void *p6 = ft_malloc(sizeof(char) * 92);
    if (p1 == NULL || p2 == NULL || p3 == NULL)
    {
        printf("Error in malloc");
    }
    ft_free(p2);
    show_alloc_mem();
    p2 = ft_malloc(3);
    show_alloc_mem();
    ft_free(p5);
    ft_free(p4);
    show_alloc_mem();
    p5 = ft_malloc(21);
    show_alloc_mem();
    p4 = ft_malloc(2);
    show_alloc_mem();
    p6 = (char *)p6 + 3;
    ft_free(p6);
    show_alloc_mem();
    return (0);
}
