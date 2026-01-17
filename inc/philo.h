/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:30:24 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:36:47 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define GRAB "has taken a fork"
# define DIE "died"

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			status;
}	t_fork;

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				meals_to_eat;
	bool			someone_died;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	write_lock;
	t_fork			**fork;
}	t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
	pthread_t		*tid;
	t_fork			*left_fork;
	t_fork			*right_fork;
	uint64_t		start_time;
	uint64_t		death_time;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	int				meals;	
	bool			is_eating;
	bool			is_dead;
	bool			is_done;
}	t_philo;

// actions.c
void		think(t_philo *philo);
void		sleep_ft(t_philo *philo);
void		grab_fork(t_philo *philo, t_fork *fork);
void		drop_fork(t_philo *philo, t_fork *fork);
void		eat(t_philo *philo);

// monitor.c
bool		monitor_death(t_philo **philo, t_data *data);
bool		monitor_meals(t_philo **philo, t_data *data);
void		*monitor(void *pointer);

// init.c
t_data		*init_data(char **token);
t_philo		*init_philo(t_data *data, int i);
void		*routine(void *philo_ptr);
t_fork		*init_fork(void);
t_philo		**init_simulation(t_data *data);

// time_handling.c
uint64_t	get_time(void);
void		ft_usleep(t_philo *philo, uint64_t time);

// utils.c
int			ft_atoi(const char *nptr);
void		ft_free(void **s, void (*clean)(void *), int i);
void		handle_deadlock(t_philo *philo, void (*func)(t_philo *, t_fork *));
void		print_action(t_philo *philo, char *action);

// lock_func.c
bool		get_isdead(t_philo *philo);
bool		get_done(t_philo *philo);
bool		get_someonedied(t_philo *philo);
void		set_isdead(t_philo *philo);

// cleaning.c
void		cleanup(t_data *data, t_philo **philo);
void		clean_philo(void *ptr);
void		clean_fork(void *ptr);
void		clean_data(void *ptr);

// threads.c
void		set_threads(t_philo **philo, t_data *data);

#endif