/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:55:02 by jubarbie          #+#    #+#             */
/*   Updated: 2018/04/20 16:47:30 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
    if (ft_malloc(2) == NULL || ft_malloc(2) == NULL || ft_malloc(sizeof(char) * 8000) == NULL) {
        printf("Error in malloc\n");
    }
    show_alloc_mem();
    return (0);
}
