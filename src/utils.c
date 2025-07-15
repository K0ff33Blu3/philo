/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:07:58 by miricci           #+#    #+#             */
/*   Updated: 2025/05/25 15:17:23 by miricci          ###   ########.fr       */
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

void	ft_free(void **s, int i)
{
	int	j;

	if (i == -1)
	{
		j = 0;
		while (s[j])
			free(s[j++]);
	}
	else
	{
		while (--i >= 0)
			free(s[i]);
	}
	free(s);
}

unsigned int	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(unsigned int time)
{
	unsigned int	start;
	unsigned int	time_in_ms;
	
	time_in_ms = time / 1000;
	start = get_time(); // ritorna tempo in millisecondi
	while ((get_time() - start) < time_in_ms)
	{
		if ((time_in_ms - (get_time() - start)) > 5)
			ft_usleep(1000); // dorme 1 millisecondo = 1000 microsecondi
		// else
		// 	; // busy-wait per gli ultimi millisecondi
	}
	return (0);
}

void	print_action(t_philo *philo, const char *action)
{
	printf("%d %d %s\n", get_time(), philo->philo_id, action);
}

