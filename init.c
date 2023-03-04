/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:30:43 by gskrasti          #+#    #+#             */
/*   Updated: 2023/03/04 12:45:51 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_info *info, int i, pthread_mutex_t	*forks)
{
	info->philo[i].id = i + 1;
	info->philo[i].times_eaten = 0;
	info->philo[i].l_fork = &forks[i];
	info->philo[i].r_fork = &forks[(i + 1) % info->count];
	info->philo[i].last_meal = info->start;
	info->philo[i].info = info;
	pthread_create(&info->philo[i].thread, NULL, philosophers, &info->philo[i]);
}
