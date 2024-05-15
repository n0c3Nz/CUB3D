/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:18:46 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:45:59 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

int	check_last_line(char *line, int j, int k, int file_lines)
{
	if (k + 1 == file_lines)
	{
		if (check_limit(line))
			return (1);
	}
	return (0);
}

void	check_alloc(t_cub *cub, int *i)
{
	(*i)++;
	cub->map.lines[*i] = malloc(sizeof(char) * cub->map.sx + 1);
	if (!cub->map.lines[*i])
	{
		ft_putstr_err("Error: Unable to allocate for map\n");
		exit(1);
	}
}
