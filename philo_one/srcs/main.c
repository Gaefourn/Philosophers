/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <gaefourn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 01:26:07 by gaefourn            #+#    #+#             */
/*   Updated: 2020/10/01 01:32:19 by gaefourn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_one.h"

int		get_params(char **av)
{
	g_banquet.nb_philos = ft_atoi(av[1]);
	g_banquet.die = ft_atoi(av[2]);
	g_banquet.eat = ft_atoi(av[3]);
	g_banquet.sleep = ft_atoi(av[4]);
	g_banquet.timetoeat = (av[5] ? ft_atoi(av[5]) : 0);
	g_banquet.alive = 0;
	if ((g_banquet.nb_philos <= 0 || g_banquet.eat <= 0 || g_banquet.eat <= 0
	|| g_banquet.sleep <= 0 || g_banquet.timetoeat < 0))
		return (FAIL);
	return (SUCCESS);
}

void	*philo_fun(void *philo)
{
	t_philo		*p;
	pthread_t	boss;
	
	p = (t_philo*)philo;
	g_banquet.start = get_time();
	p->last_meal = g_banquet.start;
	p->death_time = p->last_meal + g_banquet.die;
	if (pthread_create(&boss, NULL, heyboss, (void*)p))
		return ((void *)FAIL);
	pthread_detach(boss);
	while (1)
		ft_actions(p);
	return ((void*)SUCCESS);
}

int		init_threads(void)
{
	pthread_t		thread[g_banquet.nb_philos];
	int					i;
	
	i = -1;
	pthread_mutex_init(&g_banquet.write, NULL);	
	while (++i < g_banquet.nb_philos)
	{
		pthread_create(&thread[i], NULL, &philo_fun, (void *)(&g_banquet.philos[i]));
		pthread_detach(thread[i]);
		usleep(500);
	}
	return (SUCCESS);
}

int		init(void)
{
	int	i;
	
	i = -1;
	g_banquet.philos = NULL;
	if (!(g_banquet.philos = malloc(sizeof(t_philo) * g_banquet.nb_philos)))
		return (FAIL);
	g_banquet.mutex= NULL;
	if (!(g_banquet.mutex = malloc(sizeof(pthread_mutex_t) * 
		g_banquet.nb_philos)))
		return (FAIL);
	while (++i < g_banquet.nb_philos)
	{
			g_banquet.philos[i].pos = i;
			g_banquet.philos[i].last_meal = 0;
			g_banquet.philos[i].meal_count = 0;
			pthread_mutex_init(&g_banquet.mutex[i], NULL);
			pthread_mutex_init(&g_banquet.philos[i].eating, NULL);
			g_banquet.philos[i].lfork = i;
			g_banquet.philos[i].rfork = (i + 1 != g_banquet.nb_philos) ? i + 1 : 0;
	}
	return(init_threads());
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(1, "Wrong number of arguments.\n", 28);
		return (0);
	}
	memset(&g_banquet, 0 ,sizeof(g_banquet));
	if (get_params(av) == FAIL)
	{
		write(1, "At least 1 argument is invalid.\n", 32);
		return (FAIL);
	}
	if (init())
		return(FAIL);
	while (g_banquet.alive == 0)
		continue;
	if (g_banquet.alive == MAX_EAT_REACHED)
		print_log(&g_banquet.philos[g_banquet.which], MAX_EAT_REACHED);
	else
		print_log(&g_banquet.philos[g_banquet.which], DIED);
	ft_free();	
	return (0);
}