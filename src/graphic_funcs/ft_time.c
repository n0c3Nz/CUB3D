/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:35:49 by smagniny          #+#    #+#             */
/*   Updated: 2024/03/13 12:09:53 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D.h"

long	long	timenow(struct timeval *te)
{
	long long	time;

	gettimeofday(te, NULL);
	time = (long long)((te->tv_sec * 1000) + (te->tv_usec / 1000));
	return (time);
}