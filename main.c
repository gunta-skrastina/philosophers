/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:17:00 by gskrasti          #+#    #+#             */
/*   Updated: 2023/03/04 12:32:00 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	if (validate(argc, argv) > 0)
		return (1);
	info.count = ft_atoi(argv[1]);
	info.tt_die = ft_atoi(argv[2]);
	info.tt_eat = ft_atoi(argv[3]);
	info.tt_sleep = ft_atoi(argv[4]);
	if (info.count == 1)
	{
		printf("%d 1 died\n", info.tt_die);
		return (0);
	}
	info.t_must_eat = 0;
	if (argv[5] && ft_atoi(argv[5]) > 0)
		info.t_must_eat = ft_atoi(argv[5]);
	info.start = ft_get_time();
	info.dead = 0;
	pthread_mutex_init(&info.dying, NULL);
	philo(&info);
	free(info.philo);
	return (0);
}

int	validate(int argc, char *argv[])
{
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
	{
		printf("Wrong input\n");
		return (1);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		printf("Chill... Too many philosophers\n");
		return (2);
	}
	return (0);
}
