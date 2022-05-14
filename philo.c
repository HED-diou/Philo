/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:17:28 by hed-diou          #+#    #+#             */
/*   Updated: 2022/05/14 15:10:17 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_err_inputs(char **av)
{
	int	a;
	int	b;

	a = 1;
	while (av[a])
	{
		b = 0;
		while (av[a][b])
		{
			if (ft_isdigit(av[a][b]) == 0)
				return (0);
			b++;
		}
		a++;
	}
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
	pthread_mutex_t	msg;
	long long		time;

	time = timestamp();
	pthread_mutex_init(&msg, NULL);
	while (i < ft_atoi(av[1]))
	{
		if (ac == 5)
			table->philosof[i].nb_to_eat = -1;
		else
			table->philosof[i].nb_to_eat = ft_atoi(av[5]);
		struct_init(i, av, table, &msg);
		table->philosof[i].last_time_eat = time;
		table->philosof[i].start_time = time;
		pthread_create(&table->philosof[i].philosopher,
			NULL, &routine, &table->philosof[i]);
		usleep(50);
		i++;
	}
}

int	death_check(t_table	*table, int i, int j)
{
	while (++i < table->philosof->nb_philo)
	{
		pthread_mutex_lock(table->philosof->msg);
		if ((timestamp() - table->philosof->last_time_eat)
			>= table->philosof->time_to_die)
		{
			while (++j < table->philosof->nb_philo)
				table->philosof[j].is_death = 0;
			printf("%lld philo %d is death\n",
				timestamp() - table->philosof->start_time, i + 1);
			return (1);
		}
		if (i == table->philosof->nb_philo - 1)
			i = -1;
		pthread_mutex_unlock(table->philosof->msg);
		if (table->philosof->nb_to_eat != -1
			&& table->philosof->x_eat > table->philosof->nb_to_eat)
		{
			pthread_mutex_lock(table->philosof->msg);
			printf("END OF PROGRAME\n");
			return (1);
		}
		usleep(50);
	}
	return (0);
}

int	valid_ac(int ac)
{
	if (ac != 5 && ac != 6)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_table	*table;
	int		j;

	i = -1;
	j = -1;
	if (valid_ac(ac))
		return (0);
	if (check_err_inputs(av))
		return (0);
	table = malloc(sizeof(t_table));
	table->philosof = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&table->forks[i], NULL);
	i = 0;
	philosophers_init(av, table, i, ac);
	while (1)
	{
		i = -1;
		j = -1;
		if (death_check(table, i, j) != 0)
			return (0);
	}
}
