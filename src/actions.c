/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:57:40 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 13:35:18 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philo *philo)
{
	print_action(philo, THINK);
}

void	sleep_ft(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	grab_fork(t_philo *philo, t_fork *fork)
{
	if (!fork)
		return ;
	pthread_mutex_lock(&(fork->mutex));
	fork->status = false;
	print_action(philo, GRAB);
}

void	drop_fork(t_philo *philo, t_fork *fork)
{
	(void)philo;
	if (!fork)
		return ;
	fork->status = true;
	pthread_mutex_unlock(&(fork->mutex));
}

void	eat(t_philo *philo)
{
	handle_deadlock(philo, grab_fork);
	pthread_mutex_lock(&(philo->meal_lock));
	philo->is_eating = true;
	philo->meals++;
	if (philo->meals >= philo->data->meals_to_eat)
		philo->is_done = true;
	print_action(philo, EAT);
	pthread_mutex_unlock(&(philo->meal_lock));
	ft_usleep(philo, (uint64_t)philo->data->time_to_eat);
	pthread_mutex_lock(&(philo->meal_lock));
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->is_eating = false;
	pthread_mutex_unlock(&(philo->meal_lock));
	handle_deadlock(philo, drop_fork);
}
