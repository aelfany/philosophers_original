/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:13:16 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 16:00:45 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_parsing(t_var *x)
{
	int	a;

	a = 1;
	if (x->ac == 6)
	{
		if (x->h_m_t_eat <= 0)
		{
			error_case();
			return (0);
		}
	}
	if (x->philo <= 0 || x->die <= 0
		|| x->eat <= 0 || x->sleep <= 0)
	{
		error_case();
		return (0);
	}
	a++;
	return (1);
}

int	var_init(t_var *x, char **str, int ac)
{
	int	a;

	a = 0;
	while (str[++a])
	{
		if (check_digit(str[a]) || ft_atoi(str[a]) > INT_MAX)
			return (error_case());
	}
	pthread_mutex_init(&x -> update, NULL);
	pthread_mutex_init(&x -> print, NULL);
	pthread_mutex_init(&x -> mute, NULL);
	pthread_mutex_init(&x -> died, NULL);
	x->philo = ft_atoi(str[1]);
	x->sleep = ft_atoi(str[4]);
	x->die = ft_atoi(str[2]);
	x->eat = ft_atoi(str[3]);
	x -> count = 0;
	x->ac = ac;
	x->gg = 0;
	if (x->ac == 6)
		x->h_m_t_eat = ft_atoi(str[5]);
	else
		x->h_m_t_eat = -1;
	return (1);
}

int	check_eat_time(t_philo *a)
{
	pthread_mutex_lock(&a -> info -> mute);
	if (a -> info -> count == a -> info -> philo)
	{
		pthread_mutex_unlock(&a -> info ->mute);
		pthread_mutex_lock(&a -> info -> print);
		return (0);
	}
	pthread_mutex_unlock(&a -> info ->mute);
	return (1);
}

void	check_die(t_philo *a)
{
	while (1)
	{
		if (check_eat_time(a) == 0)
			break ;
		pthread_mutex_lock(&a -> info -> update);
		if (current_time() - a -> last_eat >= \
			(unsigned long long)a -> info -> die)
		{
			pthread_mutex_lock(&a -> info -> print);
			printf("%llu %d %s\n", current_time(),
				a -> ph_id, "died");
			pthread_mutex_lock(&a -> info -> died);
			a -> info -> gg = 1;
			pthread_mutex_unlock(&a -> info -> died);
			pthread_mutex_unlock(&a -> info -> update);
			break ;
		}
		pthread_mutex_unlock(&a -> info -> update);
		a = a -> next;
	}
}

int	main(int ac, char **av)
{
	t_var		*x;
	pthread_t	ph;
	t_philo		*a;

	x = malloc(sizeof(t_var));
	a = NULL;
	x->j = 0;
	if (ac == 6 || ac == 5)
	{
		current_time();
		if (!var_init(x, av, ac) || !check_parsing(x))
			return (0);
		ph_generator(x, &a);
		while (x->j < a -> info -> philo)
		{
			pthread_create(&ph, NULL, philo_routine, a);
			a = a -> next;
			x->j++;
		}
		check_die(a);
		pthread_mutex_lock(&a -> info -> update);
		destroy_mutex(&a);
	}
	else
		error_case();
}
