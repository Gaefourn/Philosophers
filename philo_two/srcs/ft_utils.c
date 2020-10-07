/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetan <gaetan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 21:45:46 by gaetan            #+#    #+#             */
/*   Updated: 2020/10/07 17:54:22 by gaetan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void				ft_free(void)
{
	int			i;
	char		name[50];

	i = 0;
	sem_unlink(TAKEFORKS);
	sem_unlink(FORKS);
	sem_unlink(WRITE);
	sem_unlink(DEATH);
	if (g_banquet.philos)
		while (i < g_banquet.nb_philos)
		{
			ft_name(name, i + 1);
			sem_unlink(name);
			i++;
		}
	free(g_banquet.philos);
	g_banquet.philos = NULL;
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
}

int	ft_atoi(const char *nptr)
{
	int nb;
	int i;
	int neg;

	i = 0;
	nb = 0;
	neg = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\r' ||
			nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = ((nb * 10) + (nptr[i] - 48));
		i++;
	}
	if (neg > 0)
		return (-nb);
	return (nb);
}

uint64_t			get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (uint64_t)1000 + (tv.tv_usec / 1000));
}