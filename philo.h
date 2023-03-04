/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:17:19 by gskrasti          #+#    #+#             */
/*   Updated: 2023/03/04 14:42:23 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

struct	s_info;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	int				ms_till_death;
	long long		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	struct s_info	*info;
}		t_philo;

typedef struct s_info
{
	int				count;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				t_must_eat;
	int				dead;
	pthread_mutex_t	dying;
	pthread_mutex_t	done_mutex;
	int				done;
	long long		start;
	t_philo			*philo;
}			t_info;

int			ft_atoi(char *str);
long long	ft_get_time(void);
int			print_msg(t_philo *philo, char *msg, int i);
void		*philosophers(void *arg);
void		philo(t_info *info);
int			check_if_dead(t_philo *philo);
void		do_while(long long time);
int			validate(int argc, char *argv[]);
int			ft_isnum(char *str);
void		init_philo(t_info *info, int i, pthread_mutex_t	*forks);
int			eat(t_philo *philo);
int			check_if_done(t_philo *philo);

#endif
