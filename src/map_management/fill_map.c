/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:43:03 by guortun-          #+#    #+#             */
/*   Updated: 2024/05/15 10:46:17 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

static void	initializeindices(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

static void	fill_linewithones(char *lines_i, int line_length)
{
	int	j;

	j = 0;
	while (j < line_length)
		lines_i[j++] = '1';
	lines_i[j] = '\0';
}

static	int	fill_mold(t_cub *cub, char *buffer)
{
	int	i;
	int	j;
	int	k;

	initializeindices(&i, &j, &k);
	cub->map.lines[i] = malloc(sizeof(char *) * cub->map.sx + 1);
	if (cub->map.lines[i] == NULL)
		return (ft_putstr_err("Error: malloc: Unable to allocate for map*\n"));
	while (buffer[k])
	{
		if (!check_bff_and_fill_lines(buffer[k], &cub->map.lines[i][j], &j))
		{
			while (j < cub->map.sx)
				cub->map.lines[i][j++] = '1';
			cub->map.lines[i][j] = '\0';
			if (buffer[k + 1])
			{
				check_alloc(cub, &i);
				j = 0;
			}
		}
		k++;
	}
	fill_linewithones(cub->map.lines[i], cub->map.sx);
	return (0);
}

int	fill_map(t_cub **cub, char *buffer)
{
	while (*buffer != '\0')
	{
		if (*buffer != '\n' && (*(buffer + 1) != '\0'))
			buffer++;
		else if (*buffer == '\n' && (*(buffer + 1) != '\0'))
		{
			buffer++;
			if (*buffer == '1' || *buffer == ' ')
				break ;
		}
	}
	(*cub)->map.sx = find_long_line(buffer);
	(*cub)->map.lines = allocate_memory((*cub)->map.sy);
	if ((*cub)->map.lines == NULL)
		return (ft_putstr_err("Error: malloc: Unable to allocate for map*\n"));
	if (fill_mold(*cub, buffer))
		return (1);
	return (0);
}
