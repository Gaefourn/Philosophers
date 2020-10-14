/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:13:04 by gaetan            #+#    #+#             */
/*   Updated: 2020/10/14 15:47:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		ft_name(char *name, int pos)
{
	int			i;
	const char	prefix[7] = "/philo-";

	i = -1;
	while (++i < 7)
		name[i] = prefix[i];
	while (pos)
	{
		name[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	name[i] = '\0';
}

void		*heyboss(void *philo)
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
			g_banquet.alive = DIED;
			g_banquet.which = p->pos;
			if (sem_post(p->eating))
				return ((void *)FAIL);
			return (SUCCESS);
		}
		if (sem_post(p->eating))
			return ((void *)FAIL);
	}
	return ((void *)SUCCESS);
}

void		ft_check(void)
{
	g_banquet.check++;
	if (g_banquet.check == g_banquet.nb_philos)
		g_banquet.alive = MAX_EAT_REACHED;
}

void		ft_actions(t_philo *p)
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
		ft_check();
	ft_usleep(g_banquet.eat);
	sem_post(p->eating);
	print_log(p, IS_SLEEPING);
	sem_post(g_banquet.forks);
	sem_post(g_banquet.forks);
	ft_usleep(g_banquet.sleep);
	print_log(p, IS_THINKING);
	usleep(100);
}
