/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:08:40 by efranco           #+#    #+#             */
/*   Updated: 2025/03/26 01:15:45 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_must_eat;
}		t_philo;

int		ft_atoi(const char *theString);
long	ft_atol(const char *theString);
int		ft_isdigit(int character);
void	check_line(int count, char **line);
void	check_each_arguments(int count, char **line);
void	check_one_arg(char *arg);
void	init_philo(t_philo *philo, char **line);

#endif
