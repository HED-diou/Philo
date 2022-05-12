/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:17:28 by hed-diou          #+#    #+#             */
/*   Updated: 2022/04/05 17:21:40 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_err_inputs(char **av)
{
	if (av[5])
		if (ft_atoi(av[5]) <= 0)
			return (1);
	if (ft_atoi(av[4]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[2]) <= 0 || ft_atoi(av[1]) <= 0)
		return (1);
	return (0);
}

void	philosophers_init(char **av, t_table *table, int i, int ac)
{
	while (i < ft_atoi(av[1]))
	{
		if (ac == 5)
			table->philosof[i].nb_to_eat = -1;
		else
			table->philosof[i].nb_to_eat = ft_atoi(av[5]);
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
		table->philosof[i].last_time_eat = timestamp();
		pthread_create(&table->philosof[i].philosopher,
			NULL, &routine, &table->philosof[i]);
		usleep(50);
		i++;
	}
}

int	death_check(t_table	*table, int i)
{
	while (1)
	{
		i = -1;
		while (++i < table->philosof->nb_philo)
		{
			if ((timestamp() - table->philosof->last_time_eat)
				>= table->philosof->time_to_die)
			{
				pthread_mutex_lock(&table->philosof->msg);
				printf("%lld philos %d is death\n",
					timestamp() - table->philosof->start_time, i + 1);
				table->philosof->is_death = 0;
				return (1);
			}
		}
		if (table->philosof->nb_to_eat != -1
			&& table->philosof->x_eat > table->philosof->nb_to_eat)
		{
			pthread_mutex_lock(&table->philosof->msg);
			printf("END OF PROGRAME\n");
			return (1);
		}
		usleep(10);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_table	*table;

	i = -1;
	if (ac != 5 && ac != 6)
	{
		printf("invalid arguments\n");
		return (0);
	}
	if (check_err_inputs(av))
		return (0);
	table = malloc(sizeof(t_table));
	table->philosof = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	pthread_mutex_init(&table->philosof->msg, NULL);
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&table->forks[i], NULL);
	i = 0;
	philosophers_init(av, table, i, ac);
	i = -1;
	i = 0;
	death_check(table, i);
}
