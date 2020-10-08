/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetan <gaetan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:13:04 by gaetan            #+#    #+#             */
/*   Updated: 2020/10/08 18:00:12 by gaetan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			ft_name(char *name, int pos, int eat)
{
	int			i;
	const char	prefix[7] = "/philo-";
	const char	prefix_eat[11] = "/philo-eat-";

	i = -1;
	if (eat)
		while (++i < 11)
			name[i] = prefix_eat[i];
	else
		while (++i < 7)
			name[i] = prefix[i];
	while (pos)
	{
		name[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	name[i] = '\0';
}

void			*handle_timetoeat(void *philo)
{
	int			nb_times_philos_have_eaten;
	int			i;

	(void)philo;
	nb_times_philos_have_eaten = 0;
	while (nb_times_philos_have_eaten < g_banquet.timetoeat)
	{
		i = 0;
		while (i < g_banquet.nb_philos)
			sem_wait(g_banquet.philos[i++].eat_count);
		nb_times_philos_have_eaten++;
	}
	print_log(NULL, MAX_EAT_REACHED);
	sem_post(g_banquet.stop);
	return (0);
}

void	*heyboss(void *philo)
{
	t_philo		*p;

	p = (t_philo*)philo;
	while (1)
	{
		usleep(1000);
		if (sem_wait(p->eating))
			return ((void *)FAIL);
		if (p->death_time < get_time())
		{
			print_log(p, DIED);
			g_banquet.which = p->pos;
			if (sem_post(g_banquet.stop))
				return ((void*)FAIL);
			if (sem_post(p->eating))
				return ((void *)FAIL);
			return (SUCCESS);
		}
		if (sem_post(p->eating))
			return ((void *)FAIL);
	}
	return ((void *)SUCCESS);
}

void	ft_actions(t_philo *p)
{
	sem_wait(g_banquet.take_forks);
	sem_wait(g_banquet.forks);
	print_log(p, HAS_TAKEN_A_FORK);
	sem_wait(g_banquet.forks);
	print_log(p, HAS_TAKEN_A_FORK);
	sem_post(g_banquet.take_forks);
	sem_wait(p->eating);
	p->last_meal = get_time();
	p->death_time = p->last_meal + g_banquet.die;
	print_log(p, IS_EATING);
	p->meal_count += 1;
	if (p->meal_count == g_banquet.timetoeat)
	{
		print_log(p, MAX_EAT_REACHED);
		sem_post(g_banquet.stop);
	}
	ft_usleep(g_banquet.eat);
	sem_post(p->eating);
	print_log(p, IS_SLEEPING);
	sem_post(g_banquet.forks);
	sem_post(g_banquet.forks);
	ft_usleep(g_banquet.sleep);
	print_log(p, IS_THINKING);
	usleep(100);
}