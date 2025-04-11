/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:08:28 by efranco           #+#    #+#             */
/*   Updated: 2025/04/12 00:20:45 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_struct(t_data philo, int ac)
{
	printf("number_of_philosophers : %d\n", philo.number_of_philosophers);
	printf("time_to_die : %d\n", philo.time_to_die);
	printf("time_to_eat: %d\n", philo.time_to_eat);
	printf("time_to_sleep: %d\n", philo.time_to_sleep);
	if (ac == 6)
		printf("number_of_times_must_eat: %d\n",
			philo.number_of_times_must_eat);
}
void	printf_log(int id, char *str)
{
	printf("Philosopher %d %s\n", id, str);
}

long	get_timestamp_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
void	custom_usleep(t_philo *philo)
{
	long	counter;

	counter = 0;
	pthread_mutex_lock(&philo->link->mutex_stop);
	if (philo->link->stop == 1)
	{
		pthread_mutex_unlock(&philo->link->mutex_stop);
		return ;
	}
	pthread_mutex_unlock(&philo->link->mutex_stop);
	pthread_mutex_unlock(&philo->mutex_sleeping);
	while (counter < philo->link->time_to_sleep * 1000)
	{
		usleep(10);
		counter += 10;
		if (philo->link->stop == 1)
			break;
		if (philo->last_meal_eaten + counter > philo->last_meal_eaten
			+ philo->link->time_to_die * 1000)
		{
			pthread_mutex_lock(&philo->mutex_print);
			printf("%ld %d  died\n", (get_timestamp_us() - philo->link->time_to_start) / 1000, philo->id);
			pthread_mutex_unlock(&philo->mutex_print);
			pthread_mutex_lock(&philo->link->mutex_stop);
			philo->link->stop = 1;
			pthread_mutex_unlock(&philo->link->mutex_stop);
			pthread_mutex_unlock(&philo->mutex_sleeping);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->mutex_sleeping);
}
void	*thread_routine(void *arg)
{
	t_philo			*philo;


	philo = (t_philo *)arg;
	while (philo->link->started == 0)
	;
	philo->link->time_to_start = get_timestamp_us();

	while(1)
	{

		pthread_mutex_lock(&philo->mutex_print);
		printf("%ld %d  is thinking\n", (get_timestamp_us() - philo->link->time_to_start) / 1000, philo->id);
		pthread_mutex_unlock(&philo->mutex_print);

		if(philo->id % 2 == 0)
		{
			if (philo->link->number_of_philosophers % 2 == 0)
				usleep(500);
			pthread_mutex_lock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);

			pthread_mutex_lock(&philo->mutex_print);
			printf("%ld %d  has taken a fork\n", (get_timestamp_us() - philo->link->time_to_start) / 1000, philo->id);
			pthread_mutex_unlock(&philo->mutex_print);
		}
		else
		{
			if (philo->link->number_of_philosophers % 2 != 0)
				usleep(500);
			pthread_mutex_lock(&philo->right_fork->mutex);
			pthread_mutex_lock(&philo->left_fork->mutex);

			pthread_mutex_lock(&philo->mutex_print);
			printf("%ld %d  has taken a fork\n", (get_timestamp_us() - philo->link->time_to_start) / 1000, philo->id);
			pthread_mutex_unlock(&philo->mutex_print);
		}

		pthread_mutex_lock(&philo->mutex_print);
		printf("%ld %d  is eating\n", (get_timestamp_us() - philo->link->time_to_start) / 1000, philo->id);
		pthread_mutex_unlock(&philo->mutex_print);
		usleep(philo->link->time_to_eat * 1000);

		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);

		pthread_mutex_lock(&philo->mutex_print);
		printf("%ld %d  is sleeping\n", (get_timestamp_us() - philo->link->time_to_start) / 1000, philo->id);
		pthread_mutex_unlock(&philo->mutex_print);
		custom_usleep(philo);

		pthread_mutex_lock(&philo->mutex_alive);
		if(philo->link->stop == 1)
			break;
		pthread_mutex_unlock(&philo->mutex_alive);
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
void	printf_fork(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->link->number_of_philosophers)
	{
		printf("id : %d\n", philo[i].id);
		printf("\n");
		printf("\n");
		printf("fork right : %p\n", philo[i].right_fork);
		printf("fork left : %p\n", philo[i].left_fork);
		i++;
		printf("------------------------\n");
	}
}
void	create_a_table(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return ;
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].link = data;
		philo[i].alive = true;
		pthread_mutex_init(&philo[i].mutex_alive, NULL);
		pthread_mutex_init(&philo[i].mutex_print, NULL);
		pthread_mutex_init(&philo[i].mutex_eating, NULL);
		pthread_mutex_init(&philo[i].mutex_sleeping, NULL);
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
}

int	main(int ac, char **av)
{
	t_data	data;

	check_line(ac, av);
	init_data(&data, av);
	// print_struct(data, ac);
	create_a_table(&data);
	destroy_a_table(&data);
	pthread_mutex_destroy(&data.mutex);
	return (0);
}

// usleep(500000);
// if (philo->id % 2 == 0)
// {
// 	pthread_mutex_lock(&philo->left_fork->mutex);
// 	printf_log(philo->id, "has taken a fork left");
// 	pthread_mutex_lock(&philo->right_fork->mutex);
// 	printf_log(philo->id, "has taken a fork right");
// }
// else
// {
// 	pthread_mutex_lock(&philo->right_fork->mutex);
// 	printf_log(philo->id, "has taken a fork");
// 	pthread_mutex_lock(&philo->left_fork->mutex);
// 	printf_log(philo->id, "has taken a fork");
// }
// pthread_mutex_lock(&philo->meal_mutex);
// printf_log(philo->id, "is eating");
// philo->last_meal = get_timestamp_us();
// pthread_mutex_unlock(&philo->meal_mutex);
// usleep(philo->link->time_to_eat);
// philo->meals_eaten++;
// pthread_mutex_unlock(&philo->left_fork->mutex);
// pthread_mutex_unlock(&philo->right_fork->mutex);
// printf_log(philo->id, "is sleeping");
// usleep(philo->link->time_to_sleep);
