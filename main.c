/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:55:02 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/25 18:31:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	void *p1 = ft_malloc(2);
	void *p2 = ft_malloc(23 * sizeof(int));
	void *p3 = ft_malloc(sizeof(char) * 3500);
	void *p4 = ft_malloc(sizeof(char) * 80);
	void *p5 = ft_malloc(sizeof(char) * 450);
	void *p6 = ft_malloc(sizeof(char) * 92);
	if (p1 == NULL || p2 == NULL || p3 == NULL)
	{
		printf("Error in malloc");
	}
	show_alloc_mem();
	ft_free(p2);
	show_alloc_mem();
	p2 = ft_malloc(3);
	show_alloc_mem();
	ft_free(p5);
	show_alloc_mem();
	ft_free(p4);
	show_alloc_mem();
	p5 = ft_malloc(21);
	show_alloc_mem();
	p4 = ft_malloc(2);
	show_alloc_mem();
	printf("Freeing p4\n");
	ft_free(p4);
	show_alloc_mem();
	printf("Freeing p3\n");
	ft_free(p3);
	show_alloc_mem();
	printf("Freeing p1\n");
	ft_free(p1);
	show_alloc_mem();
	printf("Freeing p2\n");
	ft_free(p2);
	show_alloc_mem();
	printf("Freeing p6\n");
	ft_free(p6);
	show_alloc_mem();
	printf("Freeing p5\n");
	ft_free(p5);
	show_alloc_mem();
	p5 = ft_malloc(40);
	if (p5 == NULL)
		printf("Oops");
	show_alloc_mem();
	ft_free(p5);
	show_alloc_mem();
	ft_free(p5);
	p5 = ft_malloc(54);
	show_alloc_mem();
	ft_free(p5);
	show_alloc_mem();
	return (0);
}
