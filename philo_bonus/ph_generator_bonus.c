/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_generator_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:16:03 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 13:04:48 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	routine_prainter(t_philo **creat, char *str)
{
	sem_wait((*creat)-> info -> print);
	if ((*creat)-> info -> die_flag == 0)
	{
		printf("%llu %d %s\n", current_time(),
			(*creat)-> ph_id, str);
	}
	sem_post((*creat)-> info -> print);
}

void	fork_locker(t_philo **creat)
{
	sem_wait((*creat)-> info -> fork);
	routine_prainter(&(*creat), "has taken a fork");
	sem_wait((*creat)-> next -> info -> fork);
	routine_prainter(&(*creat), "has taken a fork");
	routine_prainter(&(*creat), "is eating");
}

void	*philo_routine(t_philo	*creat)
{
	if (creat -> ph_id % 2 == 0)
		_usleep(100, creat);
	while (1)
	{
		if (creat -> info -> philo == 1)
		{
			sem_wait(creat -> info -> fork);
			routine_prainter(&creat, "has taken a fork");
			_usleep(creat -> info -> die, creat);
		}
		check_eat_time(creat);
		fork_locker(&creat);
		if (creat -> info -> h_m_t_eat != -1)
			creat -> must_eat++;
		_usleep(creat -> info -> eat, creat);
		creat -> last_eat = current_time();
		sem_post(creat -> info -> fork);
		sem_post(creat -> next -> info -> fork);
		routine_prainter(&creat, "is sleeping");
		_usleep(creat -> info -> sleep, creat);
		routine_prainter(&creat, "is thinking");
	}
	return (NULL);
}

void	insert(t_philo **root, t_var *x, int a)
{
	t_philo	*temp;
	t_philo	*ptr;

	temp = malloc(sizeof(t_philo));
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
