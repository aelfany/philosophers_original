/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:15:10 by abelfany          #+#    #+#             */
/*   Updated: 2023/04/09 22:15:13 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_philo **dest)
{
	pthread_mutex_destroy(&(*dest)-> info -> update);
	pthread_mutex_destroy(&(*dest)-> info -> print);
	pthread_mutex_destroy(&(*dest)-> info -> mute);
	pthread_mutex_destroy(&(*dest)-> info -> died);
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
	return (0);
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
