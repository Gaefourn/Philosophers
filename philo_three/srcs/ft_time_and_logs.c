/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_and_logs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetan <gaetan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:50:04 by gaetan            #+#    #+#             */
/*   Updated: 2020/10/08 18:04:07 by gaetan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_usleep(unsigned int n)
{
	uint64_t	start_time;

	start_time = get_time();
	while (1)
	{
		if (get_time() - start_time >= n)
			break ;
		usleep(50);
	}
}

void				add_str_to_log(char *log, int *i, char *str)
{
	int				j;

	j = -1;
	while (str[++j])
		log[(*i)++] = str[j];
}

void				add_nb_to_log(char *log, int *i, uint64_t n, char end)
{
	uint64_t		len;

	len = 1;
	while (n / len >= 10)
		len *= 10;
	while (len > 0)
	{
		log[(*i)++] = '0' + n / len % 10;
		len /= 10;
	}
	if (end == 0)
		;
	else
		log[(*i)++] = end;
}

void				add_status_to_log(char *log, int *i, const int status)
{
	if (status == HAS_TAKEN_A_FORK)
		add_str_to_log(log, i, "has taken a fork\n");
	else if (status == LEFT_FORKS)
		add_str_to_log(log, i, "has left its forks\n");
	else if (status == IS_EATING)
		add_str_to_log(log, i, "is eating\n");
	else if (status == IS_SLEEPING)
		add_str_to_log(log, i, "is sleeping\n");
	else if (status == IS_THINKING)
		add_str_to_log(log, i, "is thinking\n");
	else if (status == MAX_EAT_REACHED)
		add_str_to_log(log, i, "max eat reached\n");
	else if (status == DIED)
		add_str_to_log(log, i, "died\n");
}

void				print_log(t_philo *philo, const int status)
{
	char			log[50];
	int				i;

	memset(log, 0, 50);
	sem_wait(g_banquet.off);
	i = 0;
	add_nb_to_log(log, &i, get_time() - g_banquet.start, '\t');
	if (status != MAX_EAT_REACHED)
		add_nb_to_log(log, &i, philo->pos + 1, ' ');
	add_status_to_log(log, &i, status);
	sem_wait(g_banquet.write);
	write(1, log, i);
	sem_post(g_banquet.write);
	if (status != DIED && status != MAX_EAT_REACHED)
		sem_post(g_banquet.off);
}