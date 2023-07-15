/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extontion_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:07:53 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 10:27:10 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

unsigned long long	current_time(void)
{
	static long long	v;
	struct timeval		time;

	gettimeofday(&time, NULL);
	if (v == 0)
		v = ge_t_ime();
	return (ge_t_ime() - v);
}

int	check_digit(char *c)
{
	if (ft_strlen(c) > ft_strlen("+2147483648"))
		return (1);
	if (c[0] == '\0')
		return (1);
	if (c[0] == '+')
		c++;
	while (*c)
	{
		if (!(*c >= 48 && *c <= 57))
			return (1);
		c++;
	}
	return (0);
}

t_philo	*link_lst(t_philo **head)
{
	t_philo	*first;
	t_philo	*last;

	first = *head;
	last = *head;
	while (last-> next != NULL)
		last = last-> next;
	last -> next = first;
	return (last);
}

void	_usleep(unsigned long long whit, t_philo *x)
{
	unsigned long long	time;

	time = ge_t_ime();
	while (ge_t_ime() - time < whit)
	{
		usleep(500);
		check_die(x);
	}
}

unsigned long long	ge_t_ime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}
