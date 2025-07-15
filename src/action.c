/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:03:15 by miricci           #+#    #+#             */
/*   Updated: 2025/05/25 15:17:11 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	print_action(philo, DIE);
	ft_exit(philo->data, philo);
}

void	eating(t_philo *philo)
{
	int	time;

	take_fork(philo);
	time = get_time();
	ft_usleep(philo->data->time_to_eat * 1000);
	print_action(philo, EAT);
	philo->meals++;
	philo->is_eating = 1;
	philo->death_time = time + philo->data->time_to_die;
	pthread_mutex_unlock(philo->fork_l);
	// philo->fork_l->status = 1;
	pthread_mutex_unlock(philo->fork_r);
	// philo->fork_r->status = 1;
}

void	thinking(t_philo *philo)
{
	print_action(philo, THINK);
}

void	sleeping(t_philo *philo)
{
	struct timeval tv;

	philo->is_eating = 0;
	gettimeofday(&tv, NULL);
	print_action(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep * 1000);
}

void	take_fork(t_philo *philo)
{
	if (philo->philo_id % 2)
	{
		pthread_mutex_lock(philo->fork_l);
		pthread_mutex_lock(philo->fork_r);
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		pthread_mutex_lock(philo->fork_l);
	}
	print_action(philo, FORK);
	print_action(philo, FORK);
}
