/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_generator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:16:03 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 11:40:05 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine_prainter(t_philo **creat, char *str)
{
	pthread_mutex_lock(&(*creat)-> info -> print);
	pthread_mutex_lock(&(*creat)-> info -> died);
	if ((*creat)-> info -> gg == 0)
	{
		printf("%llu %d %s\n", current_time(),
			(*creat)-> ph_id, str);
	}
	pthread_mutex_unlock(&(*creat)-> info -> died);
	pthread_mutex_unlock(&(*creat)-> info -> print);
}

void	fork_locker(t_philo **creat)
{
	pthread_mutex_lock(&(*creat)-> fork);
	routine_prainter(&(*creat), "has taken a fork");
	pthread_mutex_lock(&(*creat)-> next -> fork);
	routine_prainter(&(*creat), "has taken a fork");
	routine_prainter(&(*creat), "is eating");
}

void	*philo_routine(void *x)
{
	t_philo	*creat;

	creat = (struct s_philo *)x;
	if (creat -> ph_id % 2 == 0)
		_usleep(creat -> info -> eat);
	while (1)
	{
		fork_locker(&creat);
		pthread_mutex_lock(&creat -> info -> update);
		creat -> last_eat = current_time();
		pthread_mutex_unlock(&creat -> info -> update);
		_usleep(creat -> info -> eat);
		pthread_mutex_lock(&creat -> info -> mute);
		if (creat -> info -> h_m_t_eat != -1)
			creat -> must_eat++;
		if (creat -> info -> h_m_t_eat == creat -> must_eat)
			creat -> info -> count++;
		pthread_mutex_unlock(&creat -> info -> mute);
		pthread_mutex_unlock(&creat -> fork);
		pthread_mutex_unlock(&creat -> next -> fork);
		routine_prainter(&creat, "is sleeping");
		_usleep(creat -> info -> sleep);
		routine_prainter(&creat, "is thinking");
	}
	return (NULL);
}

void	insert(t_philo **root, t_var *x, int a)
{
	t_philo	*temp;
	t_philo	*ptr;

	temp = malloc(sizeof(t_philo));
	pthread_mutex_init(&temp -> fork, NULL);
	temp -> ph_id = a;
	temp -> must_eat = 0;
	temp -> last_eat = 0;
	temp -> info = x;
	if (temp -> info -> h_m_t_eat != -1)
		temp -> info -> h_m_t_eat = x -> h_m_t_eat;
	else
		temp -> info -> h_m_t_eat = -1;
	temp -> next = NULL;
	if (*root == NULL)
		*root = temp;
	else
	{
		ptr = *root;
		while (ptr-> next != NULL)
			ptr = ptr->next;
		ptr -> next = temp;
	}
}

void	ph_generator(t_var *x, t_philo **creat)
{
	int	a;
	int	num;
	int	each;

	num = x -> philo;
	*creat = NULL;
	each = x -> h_m_t_eat;
	a = 1;
	while (num)
	{
		insert(&*creat, x, a);
		num--;
		a++;
	}
	link_lst(&*creat);
}
