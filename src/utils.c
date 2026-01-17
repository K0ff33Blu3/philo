/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:35:29 by miricci           #+#    #+#             */
/*   Updated: 2025/12/09 12:16:31 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sgn;

	nbr = 0;
	sgn = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sgn = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (!(*nptr >= 48 && *nptr <= 57))
			return (sgn * nbr);
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
	}
	return (sgn * nbr);
}

void	ft_free(void **s, void (*clean)(void *), int size)
{
	while (--size >= 0)
		(clean)(s[size]);
	free(s);
}

void	print_action(t_philo *philo, char *action)
{
	t_data	*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&(data->write_lock));
	if (!get_someonedied(philo))
		printf("%ld %d %s\n", get_time(), philo->id, action);
	pthread_mutex_unlock(&(data->write_lock));
}

void	handle_deadlock(t_philo *philo, void (*func)(t_philo *, t_fork *))
{
	if (philo->id % 2)
	{
		func(philo, philo->right_fork);
		func(philo, philo->left_fork);
	}
	else
	{
		func(philo, philo->left_fork);
		func(philo, philo->right_fork);
	}
}
