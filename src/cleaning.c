/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:55:09 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:39:20 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_data(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	if (data->nbr_philo)
		ft_free((void **)data->fork, clean_fork, data->nbr_philo);
	pthread_mutex_destroy(&(data->death_mutex));
	pthread_mutex_destroy(&(data->write_lock));
	free(data);
}

void	clean_fork(void *ptr)
{
	t_fork	*fork;

	fork = (t_fork *)ptr;
	pthread_mutex_destroy(&(fork->mutex));
	free(fork);
}

void	clean_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	free(philo->tid);
	pthread_mutex_destroy(&(philo->death_lock));
	pthread_mutex_destroy(&(philo->meal_lock));
	free(philo);
}

void	cleanup(t_data *data, t_philo **philo)
{
	int	size;

	size = data->nbr_philo;
	clean_data(data);
	ft_free((void **)philo, clean_philo, size);
}
