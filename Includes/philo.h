/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:08:40 by efranco           #+#    #+#             */
/*   Updated: 2025/04/17 14:47:17 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_time;

typedef struct s_fork
{
	int					flag;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_must_eat;
	long				time_to_start;
	long				all_ate;
	pthread_t			monitor_thread;
	pthread_mutex_t		mutex;
	pthread_mutex_t mutex_all_ate;
	t_philo				*philosophers;
	bool				started;
	int					stop;
	pthread_mutex_t mutex_stop; // Mutex pour protéger le flag stop
}						t_data;

typedef struct s_philo
{
	int					id;
	int					number_meals_eaten;
	long				time;
	long				last_meal_eaten;
	bool alive; // c'est ta variable partager
	pthread_t			thread;
	pthread_mutex_t		mutex_alive;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_eating;
	pthread_mutex_t		mutex_sleeping;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_data				*link;
}						t_philo;

long					get_timestamp_us(void);
void					printf_log(t_philo *philo, char *str);
int						ft_atoi(const char *theString);
long					ft_atol(const char *theString);
int						ft_isdigit(int character);
void					check_line(int count, char **line);
void					check_each_arguments(int count, char **line);
void					check_one_arg(char *arg);
void					init_data(t_data *philo, char **line);
void					create_a_table(t_data *data);
#endif
