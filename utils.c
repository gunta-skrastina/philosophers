/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:17:10 by gskrasti          #+#    #+#             */
/*   Updated: 2023/03/04 15:53:48 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	if (ft_isnum(str) != 0)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			i++;
		else
			return (1);
	}
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval	te;
	long long		ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (ms);
}

void	do_while(long long time)
{
	long long	end;

	end = ft_get_time() + time;
	while (ft_get_time() < end)
		usleep(100);
}

int	check_if_dead(t_philo *philo)
{
	if (philo->info->dead == 1)
	{
		return (1);
	}
	if (ft_get_time() - philo->last_meal > philo->info->tt_die)
	{
		if (philo->info->dead != 1)
		{
			philo->info->dead = 1;
			printf("%lld %d died\n",
				ft_get_time() - philo->info->start, philo->id);
		}
		return (1);
	}
	return (0);
}
