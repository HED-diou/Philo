/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:18:40 by hed-diou          #+#    #+#             */
/*   Updated: 2022/05/14 11:58:42 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	struct_init(int i, char **av, t_table *table, pthread_mutex_t *msg)
{
	table->philosof[i].nb_philo = ft_atoi(av[1]);
		table->philosof[i].left = &table->forks[(i + 1)
		% table->philosof->nb_philo];
	table->philosof[i].right = &table->forks[i];
	table->philosof[i].x_eat = 0;
	table->philosof[i].time_eating = ft_atoi(av[3]);
	table->philosof[i].time_to_die = ft_atoi(av[2]);
	table->philosof[i].time_to_sleap = ft_atoi(av[4]);
	table->philosof[i].id = i;
	table->philosof[i].is_death = 1;
	table->philosof[i].msg = msg;
}

int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
	{
		return (1);
	}
	return (0);
}
