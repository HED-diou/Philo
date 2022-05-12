/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-diou <hed-diou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:16:03 by hed-diou          #+#    #+#             */
/*   Updated: 2022/04/02 16:18:26 by hed-diou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_list{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	msg;
	pthread_t		philosopher;
	long long		start_time;
	int				is_death;
	int				id;
	int				x_eat;
	int				time_to_die;
	int				time_to_sleap;
	long long		last_time_eat;
	long			nb_to_eat;
	int				time_eating;
	int				nb_philo;
}t_philo;

typedef struct s_l{
	pthread_mutex_t	*forks;
	t_philo			*philosof;
}t_table;

long long	timestamp(void);
int			ft_atoi(const char *c);
void		ft_my_usleep(int sleep_time);
int			ft_isdigit(int arg);
void		thinking(t_philo *philosof);
void		sleeping(t_philo *philosof);
void		eating(t_philo *philosof);
void		*routine(void *forchita);

#endif