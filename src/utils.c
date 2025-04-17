/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:34 by efranco           #+#    #+#             */
/*   Updated: 2025/04/16 18:14:13 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
void	printf_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex_print);
		printf("%ld %d  %s\n", (get_timestamp_us()
				- philo->link->time_to_start) / 1000, philo->id, str);
		pthread_mutex_unlock(&philo->mutex_print);
}

int ft_atoi(const char *theString)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((theString[i] >= 9 && theString[i] <= 13) || (theString[i] == 32))
		i++;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			sign *= -1;
		i++;
	}
	while (theString[i] >= '0' && theString[i] <= '9' && theString[i])
	{
		res = res * 10 + (theString[i] - 48);
		i++;
	}
	return (res * sign);
}
long ft_atol(const char *theString)
{
	long	i;
	long	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((theString[i] >= 9 && theString[i] <= 13) || (theString[i] == 32))
		i++;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			sign *= -1;
		i++;
	}
	while (theString[i] >= '0' && theString[i] <= '9' && theString[i])
	{
		res = res * 10 + (theString[i] - 48);
		i++;
	}
	return (res * sign);
}
int ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	else
		return (0);
}
