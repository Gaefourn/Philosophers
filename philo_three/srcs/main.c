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

#include "philo_three.h"

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
	int					i;
	
	sem_unlink(TAKEFORKS);
	sem_unlink(FORKS);
	sem_unlink(WRITE);
	sem_unlink(DEATH);
	sem_unlink(OFF);
	g_banquet.take_forks = sem_open(TAKEFORKS, O_CREAT, 0666, 1);
	g_banquet.forks = sem_open(FORKS, O_CREAT, 0666, g_banquet.nb_philos);
	g_banquet.write = sem_open(WRITE, O_CREAT, 0666, 1);
	g_banquet.stop = sem_open(DEATH, O_CREAT, 0666, 0);
	g_banquet.off = sem_open(OFF, O_CREAT, 0666, 1);
	i = -1;
	while (++i < g_banquet.nb_philos)
	{
		g_banquet.philos[i].pid = fork();
		if (g_banquet.philos[i].pid < 0)
			return (FAIL);
		else if (g_banquet.philos[i].pid == 0)
		{
			philo_fun(&g_banquet.philos[i]);
			exit(0);
		}
		usleep(100);
	}
	return (SUCCESS);
}

int		init(void)
{
	int			i;
	char	name[50];
	
	i = -1;
	g_banquet.philos = NULL;
	if (!(g_banquet.philos = malloc(sizeof(t_philo) * g_banquet.nb_philos)))
		return (FAIL);
	while (++i < g_banquet.nb_philos)
	{
			g_banquet.philos[i].pos = i;
			g_banquet.philos[i].last_meal = 0;
			g_banquet.philos[i].meal_count = 0;
			ft_name(name, i + 1, 0);
			sem_unlink(name);
			g_banquet.philos[i].eating = sem_open(name, O_CREAT, 0666, 1);
			ft_name(name, i + 1, 1);
			sem_unlink(name);
			g_banquet.philos[i].eat_count = sem_open(name, O_CREAT, 0666, 0);
	}
	return(init_threads());
}

int	main(int ac, char **av)
{
	int	i;
	
	i = -1;
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
	sem_wait(g_banquet.stop);
	while (++i < g_banquet.nb_philos)
		kill(g_banquet.philos[i].pid, SIGKILL);	
	ft_free();	
	return (0);
}