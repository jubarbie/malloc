/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:34:34 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/01 21:29:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define M (1024 * 1024) 

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

static void print(char *s) 
{ 
	write(1, s, strlen(s)); 
}

static void	test3() 
{ 
	char *addr1; 
	char *addr3; 

	addr1 = (char*)ft_malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr3 = (char*)ft_realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
}

static void test3b()
{
	char *addr1; 
	char *addr2; 
	char *addr3; 

	addr1 = (char*)ft_malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr2 = (char*)ft_malloc(16*M); 
	addr3 = (char*)ft_realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
}

static void test4()
{
	char *addr; 

	addr = ft_malloc(16); 
	ft_free(NULL); 
	ft_free((void *)addr + 5); 
	if (ft_realloc((void *)addr + 5, 10) == NULL) 
		print("Bonjours\n"); 
}

static void	test5()
{
	ft_malloc(1024); 
	ft_malloc(1024 * 32); 
	ft_malloc(1024 * 1024); 
	ft_malloc(1024 * 1024 * 16); 
	ft_malloc(1024 * 1024 * 128); 
	show_alloc_mem();
}

static void	test6()
{
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	p1 = ft_malloc(1024); 
	p2 = ft_malloc(24); 
	p3 = ft_malloc(324); 
	p4 = ft_malloc(34); 
	ft_free(p3);
	show_alloc_mem();
	ft_free(p2);
	show_alloc_mem();
	ft_free(p4);
	show_alloc_mem();
	p1 = ft_malloc(1024 * 32); 
	ft_free(p1);
	p1 = ft_malloc(1024 * 1024); 
	ft_free(p1);
	p1 = ft_malloc(1024 * 1024 * 16); 
	ft_free(p1);
	p1 = ft_malloc(1024 * 1024 * 128); 
	ft_free(p1);
	show_alloc_mem();
}

int	main(int argc, char **argv)
{
	if (argc >= 2 && argv[1][0] == '0')
		test0();
	if (argc >= 2 && argv[1][0] == '1')
		test1();
	if (argc >= 2 && argv[1][0] == '2')
		test2();
	if (argc >= 2 && argv[1][0] == '3' && argv[1][1] == '\0')
		test3();
	if (argc >= 2 && argv[1][0] == '3' && argv[1][1] == 'b')
		test3b();
	if (argc >= 2 && argv[1][0] == '4')
		test4();
	if (argc >= 2 && argv[1][0] == '5')
		test5();
	if (argc >= 2 && argv[1][0] == '6')
		test6();
	if (argc == 3 && argv[2][0] == 'v')
		show_alloc_mem();
	return (0);
}
