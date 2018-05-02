/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:34:34 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/02 20:55:13 by jubarbie         ###   ########.fr       */
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
		addr = (char*)malloc(1024); 
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
		addr = (char*)malloc(1024);
		addr[0] = 42; 
		free(addr); 
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

	addr1 = (char*)malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr3 = (char*)realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
}

static void test3b()
{
	char *addr1; 
	char *addr2; 
	char *addr3; 

	addr1 = (char*)malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr2 = (char*)malloc(16*M); 
	addr3 = (char*)realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
}

static void test4()
{
	char *addr; 

	addr = malloc(16); 
	free(NULL); 
	free((void *)addr + 5); 
	if (realloc((void *)addr + 5, 10) == NULL) 
		print("Bonjours\n"); 
}

static void	test5()
{
	void	*p;
	p = malloc(1024); 
	p = malloc(1024 * 32); 
	p = malloc(1024 * 1024); 
	p = malloc(1024 * 1024 * 16); 
	p = malloc(1024 * 1024 * 128); 
	show_alloc_mem();
}

static void	test6()
{
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	p1 = malloc(1024); 
	p2 = malloc(24); 
	p3 = malloc(324); 
	p4 = malloc(34); 
	free(p3);
	show_alloc_mem();
	free(p2);
	show_alloc_mem();
	free(p4);
	show_alloc_mem();
	p1 = malloc(1024 * 32); 
	free(p1);
	p1 = malloc(1024 * 1024); 
	free(p1);
	p1 = malloc(1024 * 1024 * 16); 
	free(p1);
	p1 = malloc(1024 * 1024 * 128); 
	free(p1);
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
