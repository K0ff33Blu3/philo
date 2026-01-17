/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:21:53 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:35:54 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	monitor_death(t_philo **philo, t_data *data)
{
	int			i;
	bool		is_eating;
	uint64_t	time;
	uint64_t	death_time;

	i = -1;
	while (++i < data->nbr_philo)
	{
		time = get_time();
		pthread_mutex_lock(&(philo[i]->meal_lock));
		death_time = philo[i]->death_time;
		is_eating = philo[i]->is_eating;
		pthread_mutex_unlock(&(philo[i]->meal_lock));
		if (time >= death_time && !is_eating)
			return (set_isdead(philo[i]), true);
	}
	return (false);
}

bool	monitor_meals(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		if (!get_done(philo[i]))
			break ;
	if (i == data->nbr_philo)
	{
		pthread_mutex_lock(&(data->death_mutex));
		data->someone_died = true;
		pthread_mutex_unlock(&(data->death_mutex));
		return (true);
	}
	return (false);
}

void	*monitor(void *pointer)
{
	t_philo	**philo;
	t_data	*data;

	philo = (t_philo **)pointer;
	data = (t_data *)(*philo)->data;
	while (1)
	{
		if (monitor_death(philo, data) || monitor_meals(philo, data))
			return (pointer);
		usleep(1000);
	}
}
