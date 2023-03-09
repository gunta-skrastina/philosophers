/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:48:21 by gskrasti          #+#    #+#             */
/*   Updated: 2023/03/09 15:44:10 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	die_while(int i, t_philo *philo, t_info *info);

int	print_msg(t_philo *philo, char *msg, int i)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->dying);
	if (check_if_dead(philo) == 1)
	{
		pthread_mutex_unlock(&info->dying);
		return (1);
	}
	printf("%lld %d %s\n", ft_get_time() - info->start, philo->id, msg);
	if (i == 1)
		philo->times_eaten++;
	if (die_while(i, philo, info) > 0)
		return (2);
	pthread_mutex_unlock(&info->dying);
	return (0);
}

static int	die_while(int i, t_philo *philo, t_info *info)
{
	if ((i == 1 && ft_get_time() - philo->last_meal
			+ info->tt_eat > info->tt_die && info->dead == 0)
		|| (i == 2 && ft_get_time() - philo->last_meal
			+ info->tt_sleep > info->tt_die))
	{
		do_while((ft_get_time() - philo->last_meal - info->tt_die) * (-1));
		if (info->dead != 1)
		{
			info->dead = 1;
			printf("%lld %d died\n", ft_get_time() - info->start, philo->id);
		}
	}
	else if (info->t_must_eat > 0 && check_if_done(philo) == 1)
	{
		pthread_mutex_unlock(&info->dying);
		return (2);
	}
	return (0);
}
