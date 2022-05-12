/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:53:53 by hed-diou          #+#    #+#             */
/*   Updated: 2022/04/05 18:09:53 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_printf(t_philo *philosof, char *str)
{
	if (philosof->is_death == 1)
	{
		pthread_mutex_lock(&philosof->msg);
		printf("%lld philo %d %s\n", (timestamp()
				- philosof->start_time), philosof->id + 1, str);
		pthread_mutex_unlock(&philosof->msg);
	}
}

void	thinking(t_philo *philosof)
{
	is_printf(philosof, "has started thinking");
}

void	sleeping(t_philo *philosof)
{
	is_printf(philosof, "has started sleeping");
	ft_my_usleep(philosof->time_to_sleap);
}

void	eating(t_philo *philosof)
{
	pthread_mutex_lock(philosof->right);
	is_printf(philosof, "take the a right fork");
	pthread_mutex_lock(philosof->left);
	is_printf(philosof, "take the a left fork");
	is_printf(philosof, "has started eating");
	philosof->x_eat++;
	philosof->last_time_eat = timestamp();
	ft_my_usleep(philosof->time_eating);
	pthread_mutex_unlock(philosof->right);
	pthread_mutex_unlock(philosof->left);
}

void	*routine(void *forchita)
{
	t_philo	*philosof;
	int		i;

	i = 0;
	philosof = (t_philo *)forchita;
	philosof->start_time = timestamp();
	while (1)
	{
		eating(philosof);
		sleeping(philosof);
		thinking(philosof);
		usleep(20);
	}
	return (NULL);
}
