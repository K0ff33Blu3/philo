/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:53:34 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:34:56 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->data->nbr_philo == 1)
	{
		grab_fork(philo, philo->left_fork);
		ft_usleep(philo, (uint64_t)philo->data->time_to_die);
		drop_fork(philo, philo->left_fork);
		return (philo_ptr);
	}
	while (!get_someonedied(philo))
	{
		if (get_someonedied(philo))
			return (NULL);
		eat(philo);
		if (get_someonedied(philo))
			return (NULL);
		sleep_ft(philo);
		if (get_someonedied(philo))
			return (NULL);
		think(philo);
		if (get_someonedied(philo))
			return (NULL);
	}
	return (philo_ptr);
}

void	set_threads(t_philo **philo, t_data *data)
{
	int			i;
	pthread_t	tid;

	i = -1;
	if (pthread_create(&tid, NULL, &monitor, (void *)philo))
		return ((void)printf("Error\n"));
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_create(philo[i]->tid, NULL, &routine, (void *)philo[i]))
			return (cleanup(data, philo));
	}
	if (pthread_join(tid, NULL))
		return (cleanup(data, philo));
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(*(philo[i]->tid), NULL))
			return (cleanup(data, philo));
	}
}
