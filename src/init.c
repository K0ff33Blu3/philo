/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:17:08 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:32:54 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char **token)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nbr_philo = ft_atoi(token[1]);
	data->time_to_die = ft_atoi(token[2]);
	data->time_to_eat = ft_atoi(token[3]);
	data->time_to_sleep = ft_atoi(token[4]);
	if (token[5])
		data->meals_to_eat = ft_atoi(token[5]);
	else
		data->meals_to_eat = INT_MAX;
	data->someone_died = false;
	pthread_mutex_init(&(data->death_mutex), NULL);
	pthread_mutex_init(&(data->write_lock), NULL);
	return (data);
}

t_philo	*init_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = data;
	philo->tid = (pthread_t *)malloc(sizeof(pthread_t));
	if (!philo->tid)
		return (NULL);
	philo->left_fork = data->fork[i];
	philo->right_fork = data->fork[(i + 1) % data->nbr_philo];
	if (data->nbr_philo == 1)
		philo->right_fork = NULL;
	philo->id = i + 1;
	philo->start_time = get_time();
	philo->death_time = philo->start_time + data->time_to_die;
	pthread_mutex_init(&philo->death_lock, NULL);
	pthread_mutex_init(&philo->meal_lock, NULL);
	philo->meals = 0;
	philo->is_eating = false;
	philo->is_dead = false;
	philo->is_done = false;
	return (philo);
}

t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	pthread_mutex_init(&(fork->mutex), NULL);
	fork->status = true;
	return (fork);
}

t_philo	**init_simulation(t_data *data)
{
	t_philo	**philo;
	int		i;

	i = -1;
	data->fork = (t_fork **)malloc(sizeof(t_fork) * data->nbr_philo);
	philo = (t_philo **)malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->fork || !philo)
		return (NULL);
	while (++i < data->nbr_philo)
	{
		data->fork[i] = init_fork();
		if (!data->fork[i])
			return (ft_free((void **)(data->fork), clean_fork, i), NULL);
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i] = init_philo(data, i);
		if (!philo[i])
			return (ft_free((void **)philo, clean_philo, i), NULL);
	}
	return (philo);
}
