/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:22:40 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:35:02 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_isdead(t_philo *philo)
{
	t_data	*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&(data->death_mutex));
	data->someone_died = true;
	pthread_mutex_unlock(&(data->death_mutex));
	pthread_mutex_lock(&(philo->death_lock));
	philo->is_dead = true;
	pthread_mutex_unlock(&(philo->death_lock));
	pthread_mutex_lock(&(data->write_lock));
	printf("%ld %d died\n", get_time(), philo->id);
	pthread_mutex_unlock(&(data->write_lock));
}

bool	get_someonedied(t_philo *philo)
{
	bool	status;
	t_data	*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&(data->death_mutex));
	status = data->someone_died;
	pthread_mutex_unlock(&(data->death_mutex));
	return (status);
}

bool	get_isdead(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&(philo->death_lock));
	status = philo->is_dead;
	pthread_mutex_unlock(&(philo->death_lock));
	return (status);
}

bool	get_done(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&(philo->meal_lock));
	status = philo->is_done;
	pthread_mutex_unlock(&(philo->meal_lock));
	return (status);
}
