/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:45:20 by rnoriko           #+#    #+#             */
/*   Updated: 2022/01/20 03:19:25 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*finish_monitor(void *arg)
{
	int		i;
	t_info	*info;

	info = arg;
	sem_wait(info->finish);
	i = 0;
	while (i < info->num_of_philosophers)
		kill(info->philosophers[i++].pid, SIGTERM);
	return (NULL);
}

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;
	int		i;

	info = argv;
	i = 0;
	while (i++ < info->num_of_philosophers)
		sem_wait(info->num_of_eat_finish_philosophers);
	sem_post(info->finish);
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philosopher	*philosopher;
	struct timeval	now;
	long long		ms;

	philosopher = argv;
	while (1)
	{
		sem_wait(philosopher->check);
		sem_wait(philosopher->info->acting);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philosopher->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philosopher->info->time_to_die)
		{
			printf("%lld\t%d\t %s\n", \
				time_to_ms(now) - time_to_ms(philosopher->info->create_at), \
				philosopher->n + 1, "died");
			sem_post(philosopher->info->finish);
			return (NULL);
		}
		sem_post(philosopher->info->acting);
		sem_post(philosopher->check);
	}
	return (NULL);
}
