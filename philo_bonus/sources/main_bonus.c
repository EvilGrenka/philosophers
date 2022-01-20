/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:52:33 by rnoriko           #+#    #+#             */
/*   Updated: 2022/01/20 03:18:19 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	join_and_free_philosophers(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->num_of_philosophers)
	{
		waitpid(info->philosophers[i].pid, &status, 0);
		sem_close(info->philosophers[i].check);
		free(info->philosophers[i].name);
	}
	free(info->philosophers);
	sem_close(info->finish);
	sem_close(info->acting);
	sem_close(info->forks);
	sem_close(info->num_of_eat_finish_philosophers);
}

static void	fork_philosophers(t_info *info)
{
	int			i;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		info->philosophers[i].last_time_to_eat = info->create_at;
		info->philosophers[i].pid = fork();
		if (info->philosophers[i].pid == 0)
			return (action_philosopher(&info->philosophers[i]));
		else if (info->philosophers[i].pid < 0)
		{
			ft_puterror("ERROR: fork failed");
			exit(1);
		}
		++i;
	}
}

int	main(int argc, char *argv[])
{
	t_info		info;
	pthread_t	thread;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (ft_puterror("ERROR: wrong argc\n"));
	if (initialization_philosophers(&info, argc, argv))
		return (1);
	fork_philosophers(&info);
	if (info.num_of_must_eat != 0)
		pthread_create(&thread, NULL, monitor_each_must_eat, &info);
	pthread_create(&thread, NULL, finish_monitor, &info);
	join_and_free_philosophers(&info);
	return (0);
}
