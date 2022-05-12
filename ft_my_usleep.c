/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_usleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:25:15 by hed-diou          #+#    #+#             */
/*   Updated: 2022/04/05 18:12:17 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_my_usleep(int sleep_time)
{
	long long	before;

	before = timestamp();
	while (1)
	{
		if (timestamp() - before >= sleep_time)
			break ;
		usleep(400);
	}
}
