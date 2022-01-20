/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_philosophers_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:48:05 by rnoriko           #+#    #+#             */
/*   Updated: 2022/01/20 03:16:02 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static sem_t	*ft_sem_init(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

static void	parsing_arg(t_info *info, int argc, char *argv[])
{
	info->num_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
}

static int	check_info(t_info *info, int argc)
{
	if (argc == 6 && info->num_of_must_eat <= 0)
		return (ft_puterror("ERROR: wrong num of must eat\n"));
	if (info->num_of_philosophers < 0)
		return (ft_puterror("ERROR: wrong num of philo\n"));
	if (info->time_to_die < 0)
		return (ft_puterror("ERROR: wrong time to die\n"));
	if (info->time_to_eat < 0)
		return (ft_puterror("ERROR: wrong time to eat\n"));
	if (info->time_to_sleep < 0)
		return (ft_puterror("ERROR: wrong time to sleep\n"));
	return (FT_SUCCESS);
}

static int	init_philosophers(t_info *info)
{
	int		i;

	info->finish = ft_sem_init("finish", 0);
	info->acting = ft_sem_init("acting", 1);
	info->forks = ft_sem_init("forks", info->num_of_philosophers + 1);
	info->num_of_eat_finish_philosophers \
		= ft_sem_init("num_of_eat_finish_philo", 0);
	if (ft_malloc(&info->philosophers, sizeof(t_philosopher) \
		* info->num_of_philosophers))
		return (ft_puterror("ERROR: malloc failed\n"));
	i = 0;
	while (i < info->num_of_philosophers)
	{
		info->philosophers[i].name = make_n_name("philo", i);
		info->philosophers[i].check \
			= ft_sem_init(info->philosophers[i].name, 1);
		info->philosophers[i].n = i;
		info->philosophers[i].info = info;
		++i;
	}
	return (FT_SUCCESS);
}

int	initialization_philosophers(t_info *info, int argc, char *argv[])
{
	parsing_arg(info, argc, argv);
	if (check_info(info, argc))
		return (FT_ERROR);
	if (init_philosophers(info))
		return (FT_ERROR);
	return (FT_SUCCESS);
}
