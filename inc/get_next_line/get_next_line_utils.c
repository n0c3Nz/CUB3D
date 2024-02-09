/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:22:44 by guortun-          #+#    #+#             */
/*   Updated: 2024/02/05 20:50:47 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*realloc_buffer(char *ptr, size_t l1, size_t l2)
{
	char		*aux;
	size_t		l;

	if (l1 < l2)
		l = l2 - l1 + 1;
	if (l2 <= l1)
		l = l1 - l2 + 1;
	aux = (char *)ft_calloc(l + 1, sizeof(char));
	if (!aux)
		return (NULL);
	aux[l] = '\0';
	aux = ft_memcpy(aux, &ptr[l2], l);
	free(ptr);
	ptr = NULL;
	return (aux);
}

