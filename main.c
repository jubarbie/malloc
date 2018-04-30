/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:34:34 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/30 19:17:47 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdlib.h>

static void	test0()
{
	int i; 

	i = 0; 
	while (i < 1024) 
	{ 
		i++; 
	} 
}

static void  test1()
{
	int i; 
	char *addr; 

	i = 0; 
	while (i < 1024) 
	{ 
		addr = (char*)ft_malloc(1024); 
		addr[0] = 42; 
		i++; 
	} 
}

static void	test2()
{
	int i; 
	char *addr; 

	i = 0; 
	while (i < 1024) 
	{ 
		addr = (char*)ft_malloc(1024);
		addr[0] = 42; 
		ft_free(addr); 
		i++; 
	} 
}

int	main(int argc, char **argv)
{
	if (argc >= 2 && argv[1][0] == '0')
		test0();
	if (argc >= 2 && argv[1][0] == '1')
		test1();
	if (argc >= 2 && argv[1][0] == '2')
		test2();
	if (argc == 3 && argv[2][0] == 'v')
		show_alloc_mem();
	return (0);
}
