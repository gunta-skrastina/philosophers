/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:49:44 by gskrasti          #+#    #+#             */
/*   Updated: 2023/03/09 04:31:35 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo(t_info *info)
{
	int				i;
	pthread_mutex_t	*forks;
	int				l_fork;
	int				r_fork;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->count);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *) * info->count);
	if (info->philo == NULL || forks == NULL)
		return ;
	i = -1;
	while (++i < info->count)
		pthread_mutex_init(&forks[i], NULL);
	i = info->count;
	while (--i >= 0)
		init_philo(info, i, forks);
	i = -1;
	while (++i < info->count)
		pthread_join(info->philo[i].thread, NULL);
	i = -1;
	while (++i < info->count)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&info->dying);
	pthread_mutex_destroy(&info->done_mutex);
	free(forks);
}

void	*philosophers(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		do_while(philo->info->tt_eat);
	pthread_mutex_init(&philo->info->done_mutex, NULL);
	while (42)
	{
		if (eat(philo) == 1)
			break ;
		if (philo->info->t_must_eat > 0
			&& philo->times_eaten >= philo->info->t_must_eat)
		{
			pthread_mutex_lock(&philo->info->done_mutex);
			philo->info->done++;
			pthread_mutex_unlock(&philo->info->done_mutex);
		}
	}
	return (NULL);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (print_msg(philo, "has taken a fork", 0))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(philo->l_fork);
	if (print_msg(philo, "has taken a fork", 0))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	if (print_msg(philo, "is eating", 1))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	do_while(philo->info->tt_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->last_meal = ft_get_time();
	if (print_msg(philo, "is sleeping", 2))
		return (1);
	do_while(philo->info->tt_sleep);
	if (print_msg(philo, "is thinking", 0))
		return (1);
	return (0);
}

int	check_if_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->done_mutex);
	if (philo->info->done >= philo->info->count)
	{
		pthread_mutex_unlock(&philo->info->done_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->done_mutex);
	return (0);
}
