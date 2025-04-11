/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:57:44 by efranco           #+#    #+#             */
/*   Updated: 2025/04/07 16:48:28 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_one_arg(char *arg)
{
	int		i;
	long	number;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			printf("Not a digit argument\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	number = ft_atol(arg);
	if (number <= 0)
	{
		printf("Error: Below 1\n");
		exit(EXIT_FAILURE);
	}
	if (number > INT_MAX)
	{
		printf("Error: Above INT_MAX\n");
		exit(EXIT_FAILURE);
	}
}
void	check_each_arguments(int count, char **line)
{
	int	i;

	i = 1;
	while (i < count)
	{
		check_one_arg(line[i]);
		i++;
	}
}
void	check_line(int count, char **line)
{
	if (count != 5 && count != 6)
	{
		printf("Error: not enough arguments\n");
		exit(EXIT_FAILURE);
	}
	check_each_arguments(count, line);
}
void	init_data(t_data *philo, char **line)
{
	philo->number_of_philosophers = ft_atoi(line[1]);
	philo->time_to_die = ft_atoi(line[2]);
	philo->time_to_eat = ft_atoi(line[3]);
	philo->time_to_sleep = ft_atoi(line[4]);
	if(line[5])
		philo->number_of_times_must_eat = ft_atoi(line[5]);
	pthread_mutex_init(&philo->mutex, NULL);
}
