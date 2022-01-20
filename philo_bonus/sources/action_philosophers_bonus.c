/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philosophers_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:25:24 by rnoriko           #+#    #+#             */
/*   Updated: 2022/01/20 03:12:39 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	pickup_fork(t_philosopher *philosopher)
{
	sem_wait(philosopher->info->forks);
	print_philosophers_msg(philosopher, "has taken a fork");
	sem_wait(philosopher->info->forks);
	print_philosophers_msg(philosopher, "has taken a fork");
}

static void	eating(t_philosopher *philosopher)
{
	sem_wait(philosopher->check);
	gettimeofday(&philosopher->last_time_to_eat, NULL);
	print_philosophers_msg(philosopher, "is eating");
	philosopher->num_of_eat += 1;
	if (philosopher->num_of_eat == philosopher->info->num_of_must_eat)
		sem_post(philosopher->info->num_of_eat_finish_philosophers);
	usleep(philosopher->info->time_to_eat * 1000);
	sem_post(philosopher->info->forks);
	sem_post(philosopher->info->forks);
	sem_post(philosopher->check);
}

static void	sleeping(t_philosopher *philosopher)
{
	print_philosophers_msg(philosopher, "is sleeping");
	usleep(philosopher->info->time_to_sleep * 1000);
}

static void	thinking(t_philosopher *philosopher)
{
	print_philosophers_msg(philosopher, "is thinking");
}

void	action_philosopher(t_philosopher *philosopher)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitor, philosopher);
	if (philosopher->n % 2 == 0)
		usleep(philosopher->info->time_to_eat * 1000);
	while (1)
	{
		pickup_fork(philosopher);
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	exit(0);
}
