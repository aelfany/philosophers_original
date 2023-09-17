/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:15:10 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 16:50:45 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_die(t_philo *a)
{
	if (current_time() - a -> last_eat >= \
		(unsigned long long)a -> info -> die)
	{
		sem_wait(a -> info -> print);
		printf("%llu %d %s\n", current_time(),
			a -> ph_id, "died");
		exit(0);
	}
	return (0);
}

void	destroy_semaphore(void)
{
	sem_unlink("/fork");
	sem_unlink("/print");
}

size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

int	error_case(void)
{
	printf("\033[1;31mError!\033[0m\n");
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int		a;
	size_t	res;
	int		nb;

	a = 0;
	nb = 1;
	res = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == ' ')
		a++;
	if (str[a] == '-')
		nb *= -1;
	if (str[a] == '+' || str[a] == '-')
		a++;
	while (str[a] >= 48 && str[a] <= 57)
	{
		res *= 10;
		res = res + str[a] - 48;
		a++;
	}
	return (res * nb);
}
