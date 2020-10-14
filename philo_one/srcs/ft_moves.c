/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:13:04 by gaetan            #+#    #+#             */
/*   Updated: 2020/10/14 13:13:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*heyboss(void *philo)
{
	t_philo *p;

	p = (t_philo*)philo;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&p->eating);
		if (p->death_time < get_time())
		{
			g_banquet.alive = DIED;
			g_banquet.which = p->pos;
			pthread_mutex_unlock(&p->eating);
			break ;
		}
		pthread_mutex_unlock(&p->eating);
	}
	return ((void*)DIED);
}

void	ft_actions(t_philo *p)
{
	pthread_mutex_lock(&g_banquet.mutex[p->pos % 2 ? p->rfork : p->lfork]);
	print_log(p, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&g_banquet.mutex[p->pos % 2 ? p->lfork : p->rfork]);
	print_log(p, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&p->eating);
	p->last_meal = get_time();
	p->death_time = p->last_meal + g_banquet.die;
	print_log(p, IS_EATING);
	p->meal_count += 1;
	ft_usleep(g_banquet.eat);
	pthread_mutex_unlock(&g_banquet.mutex[p->pos % 2 ? p->rfork : p->pos]);
	pthread_mutex_unlock(&g_banquet.mutex[p->pos % 2 ? p->pos : p->rfork]);
	pthread_mutex_unlock(&p->eating);
	if (p->meal_count == g_banquet.timetoeat)
		g_banquet.alive = MAX_EAT_REACHED;
	print_log(p, IS_SLEEPING);
	ft_usleep(g_banquet.sleep);
	print_log(p, IS_THINKING);
	usleep(100);
}
