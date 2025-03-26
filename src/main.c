/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:08:28 by efranco           #+#    #+#             */
/*   Updated: 2025/03/26 01:24:11 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_struct(t_philo philo, int ac)
{
	printf("number_of_philosophers : %d\n", philo.number_of_philosophers);
	printf("time_to_die : %d\n", philo.time_to_die);
	printf("time_to_eat: %d\n", philo.time_to_eat);
	printf("time_to_sleep: %d\n", philo.time_to_sleep);
	if (ac == 6)
		printf("number_of_times_must_eat: %d\n", philo.number_of_times_must_eat);
}
int main(int ac, char **av)
{
	t_philo	philo;

	check_line(ac, av);
	init_philo(&philo, av);
	print_struct(philo, ac);
	return (0);
}
