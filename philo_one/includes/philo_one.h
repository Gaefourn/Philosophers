#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdint.h>

# define SUCCESS							0
# define FAIL										1
# define HAS_TAKEN_A_FORK		2
# define IS_EATING							3
# define IS_SLEEPING						4
# define IS_THINKING					5
# define LEFT_FORKS						6
# define MAX_EAT_REACHED		7
# define DIED									8

typedef struct 			s_philo
{
	int								pos;
	uint64_t					last_meal;
	uint64_t					death_time;
	int								rfork;
	int								lfork;
	int								meal_count;
	pthread_mutex_t		eating;
}								t_philo;


typedef struct				s_data
{
	t_philo						*philos;
	int 							nb_philos;
	int								timetoeat;
	uint64_t					die;
	uint64_t					eat;
	uint64_t					sleep;
	uint64_t					start;
	int								alive;
	int								which;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		write;
}									t_data;

t_data							g_banquet;

int								ft_atoi(const char *nptr);
void						ft_putnbr_fd(int n, int fd);
uint64_t					get_time(void);
void						*heyboss(void *philo);
void						ft_usleep(unsigned int n);
void						ft_actions(t_philo *p);
void						print_log(t_philo *philo, const int status);
int								ft_free(void);

#endif