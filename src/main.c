/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:08:28 by efranco           #+#    #+#             */
/*   Updated: 2025/04/17 15:35:47 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_if_dead(t_philo *philo)
{

	int	stop;

	pthread_mutex_lock(&philo->link->mutex_stop);
	stop = philo->link->stop;
	pthread_mutex_unlock(&philo->link->mutex_stop);
	return (stop);
}
int  check_must_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->link->mutex_stop);
	if (philo->link->number_of_times_must_eat == philo->number_meals_eaten)
	{
		pthread_mutex_unlock(&philo->link->mutex_stop);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->link->mutex_stop);
		return (0);
	}
}

void	custom_usleep(t_philo *philo, long duration_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_timestamp_us();
	while (1)
	{
		if (check_if_dead(philo))
			break;
		current_time = get_timestamp_us();
		if ((current_time - start_time) >= duration_ms * 1000)
			break;
		usleep(250);
	}
}


void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->link->started == 0)
		;
	philo->link->time_to_start = get_timestamp_us();
	while (1)
	{
		if (check_if_dead(philo))
			break;

		printf_log(philo, "is thinking");
		pthread_mutex_lock(&philo->mutex_time);
		philo->time = get_timestamp_us();
		pthread_mutex_unlock(&philo->mutex_time);

		if (philo->id % 2 == 0)
		{
			if (philo->link->number_of_philosophers % 2 == 0)
			usleep(500);
			pthread_mutex_lock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);
			if (check_if_dead(philo))
			{
				pthread_mutex_unlock(&philo->right_fork->mutex);
				pthread_mutex_unlock(&philo->left_fork->mutex);
				break;
			}
			printf_log(philo, "has taken a fork");
		}
		else
		{
			if (philo->link->number_of_philosophers % 2 != 0)
			usleep(500);
			pthread_mutex_lock(&philo->right_fork->mutex);
			pthread_mutex_lock(&philo->left_fork->mutex);
			if (check_if_dead(philo))
			{
				pthread_mutex_unlock(&philo->right_fork->mutex);
				pthread_mutex_unlock(&philo->left_fork->mutex);
				break;
			}
			printf_log(philo, "has taken a fork");
		}

		if (check_if_dead(philo))
			break;

		printf_log(philo, "is eating");
		custom_usleep(philo, philo->link->time_to_eat);
		pthread_mutex_lock(&philo->mutex_time);
		philo->last_meal_eaten = get_timestamp_us();
		philo->number_meals_eaten += 1;
		pthread_mutex_unlock(&philo->mutex_time);

		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);

		if (check_if_dead(philo) || check_must_eat(philo) == 1)
		{
			pthread_mutex_lock(&philo->link->mutex_all_ate);
			philo->link->all_ate++;
			pthread_mutex_unlock(&philo->link->mutex_all_ate);
			break;
		}

		printf_log(philo, "is sleeping");
		custom_usleep(philo, philo->link->time_to_sleep);
	}
	return (NULL);
}
t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->flag = 0;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	t_philo	*current;
	int		i;
	long	time;

	data = arg;
	while(1)
	{
		i = 0;
		while(i < data->number_of_philosophers)
		{
			current = &data->philosophers[i];
			pthread_mutex_lock(&current->mutex_eating);
			time = (get_timestamp_us() - data->time_to_start) - current->last_meal_eaten;
			pthread_mutex_unlock(&current->mutex_eating);
			if (time > data->time_to_die * 1000)
			{
				pthread_mutex_lock(&data->mutex_stop);
				data->stop = 1;
				pthread_mutex_unlock(&data->mutex_stop);

				printf_log(current, "died");
				return (NULL);
			}
			i++;
		}
		pthread_mutex_lock(&data->mutex_all_ate);
		if (data->number_of_times_must_eat > 0
			&& data->all_ate >= data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->mutex_stop);
			data->stop = 1;
			pthread_mutex_unlock(&data->mutex_stop);

			pthread_mutex_unlock(&data->mutex_all_ate);
			return (NULL);
		}
		pthread_mutex_unlock(&data->mutex_all_ate);
		usleep(500);
	}
}
void	create_a_table(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return ;
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].link = data;
		philo[i].last_meal_eaten = 0;
		philo[i].number_meals_eaten = 0;
		pthread_mutex_init(&philo[i].mutex_alive, NULL);
		pthread_mutex_init(&philo[i].mutex_print, NULL);
		pthread_mutex_init(&philo[i].mutex_eating, NULL);
		pthread_mutex_init(&philo[i].mutex_sleeping, NULL);
		pthread_mutex_init(&philo[i].mutex_time, NULL);
		if (i + 1 == data->number_of_philosophers)
		{
			philo[i].right_fork = init_fork();
			philo[i].left_fork = philo[i - 1].right_fork;
			philo[0].left_fork = philo[i].right_fork;
		}
		else if (i != 0)
		{
			philo[i].right_fork = init_fork();
			philo[i].left_fork = philo[i - 1].right_fork;
		}
		else
		{
			philo[i].right_fork = init_fork();
		}
		pthread_create(&philo[i].thread, NULL, thread_routine, &philo[i]);
		usleep(10000);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, &monitoring, data);
	data->philosophers = philo;
	data->started = true;
}
void	destroy_a_table(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
}
int	main(int ac, char **av)
{
	t_data	data;

	check_line(ac, av);
	init_data(&data, av);
	if (data.number_of_philosophers == 1)
	{
		printf("%d %d  is thinking\n", 0, 1);
		printf("%d %d  died\n", data.time_to_die, 1);
		return (0);
	}
	create_a_table(&data);
	destroy_a_table(&data);
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
