/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:11:10 by rnoriko           #+#    #+#             */
/*   Updated: 2022/01/20 03:14:56 by rnoriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_puterror(char *err_msg)
{
	char	*begin_msg;

	begin_msg = err_msg;
	while (*err_msg)
		err_msg++;
	write(2, begin_msg, err_msg - begin_msg);
	return (FT_ERROR);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	while (*nptr == '\f' || *nptr == '\r' || *nptr == ' '
		|| *nptr == '\t' || *nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		result = (result * 10) + (*nptr++ - '0');
	return (result * sign);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (FT_ERROR);
	memset(*(void **)dst, 0, size);
	return (FT_SUCCESS);
}

long long	time_to_ms(struct timeval now)
{
	long long	ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	print_philosophers_msg(t_philosopher *philosopher, char *str)
{
	long long		ms;
	struct timeval	now;

	sem_wait(philosopher->info->acting);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philosopher->info->create_at);
	printf("%lld\t%d\t %s\n", ms, philosopher->n + 1, str);
	sem_post(philosopher->info->acting);
}
