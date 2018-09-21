/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:34:34 by jubarbie          #+#    #+#             */
/*   Updated: 2018/05/04 17:29:53 by jubarbie         ###   ########.fr       */
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
	while (i < 10)
	{
		addr = (char*)malloc(512);
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
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
	void	*p5;
	void	*p6;
	void	*p7;
	void	*p8;
	void	*p9;
	void 	*p10;
	size_t	sz, pz;

	p1 = malloc(1);
	p2 = malloc(10);
	p3 = malloc(100);
	p4 = malloc(200);
	p5 = malloc(500);
	p6 = malloc(512);
	p7 = malloc(1024);
	p8 = malloc(2048);
	free(p2);
	show_alloc_mem();
	p9 = realloc(p8, 40000);
	p10 = realloc(p6, 520);
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
