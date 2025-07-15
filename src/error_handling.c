/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:45:56 by miricci           #+#    #+#             */
/*   Updated: 2025/05/25 14:47:53 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(char *s)
{
	while (s)
		write(STDERR_FILENO, s++, 1);
	write(STDERR_FILENO, " ERROR\n", 7); 
}

void	ft_exit(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&(data->fork[i]));
	clear_data(data, philo);
}

void	clear_data(t_data *data, t_philo *philo)
{
	if (data)
		free(data);
	if (philo)
		free(philo);
}