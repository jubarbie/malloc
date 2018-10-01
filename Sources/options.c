/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 12:40:06 by jubarbie          #+#    #+#             */
/*   Updated: 2018/09/29 12:40:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

char	has_env(const char *var, const char *value)
{
	return (getenv(var) && !ft_strcmp(getenv(var), value));
}

char	is_debug(void)
{
	return (g_mem.options & (1 << 1));
}

char	is_details(void)
{
	return (g_mem.options & (1 << 2));
}

void	init_options(void)
{
	if (g_mem.options == 0)
	{
		if (has_env("MALLOC_DEBUG", "y"))
			g_mem.options |= (1 << 1);
		if (has_env("MALLOC_DETAILS", "y"))
			g_mem.options |= (1 << 2);
		g_mem.options |= (1 << 0);
	}
}
