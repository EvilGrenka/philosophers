/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:03:04 by rnoriko           #+#    #+#             */
/*   Updated: 2022/01/20 02:41:59 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# define FT_ERROR		1
# define FT_SUCCESS		0

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				n;
	int				num_of_eat;
	char			*name;
	sem_t			*check;
	pid_t			pid;
	struct s_info	*info;
	struct timeval	last_time_to_eat;

}					t_philosopher;

typedef struct s_info
{
	int				num_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	sem_t			*acting;
	sem_t			*num_of_eat_finish_philosophers;
	sem_t			*finish;
	sem_t			*forks;
	t_philosopher	*philosophers;
	struct timeval	create_at;
}			t_info;

int			ft_puterror(char *err_msg);
int			ft_atoi(const char *nptr);
int			ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void		print_philosophers_msg(t_philosopher *philosopher, char *str);

char		*make_n_name(char *name, int n);

int			initialization_philosophers(t_info *info, int argc, char *argv[]);
void		action_philosopher(t_philosopher *philosopher);
void		*monitor(void *argv);
void		*finish_monitor(void *arg);
void		*monitor_each_must_eat(void *argv);

#endif