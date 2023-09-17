/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:13:16 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 16:57:05 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	check_eat_time(t_philo *a)
{
	if (a -> must_eat == a -> info -> h_m_t_eat)
		exit(2);
}

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
	x->a = 0;
	while (str[++x->a])
		if (check_digit(str[x->a]) || ft_atoi(str[x->a]) > INT_MAX)
			return (error_case());
	sem_close(x -> print);
	sem_close(x -> fork);
	destroy_semaphore();
	x -> print = sem_open("/print", O_CREAT, 777, 1);
	if (x -> print == SEM_FAILED)
		return (error_case());
	x -> fork = sem_open("/fork", O_CREAT, 777, ft_atoi(str[1]));
	if (x -> fork == SEM_FAILED)
		return (error_case());
	x->philo = ft_atoi(str[1]);
	x->sleep = ft_atoi(str[4]);
	x->die = ft_atoi(str[2]);
	x->eat = ft_atoi(str[3]);
	x -> count = 0;
	x->ac = ac;
	if (x->ac == 6)
		x->h_m_t_eat = ft_atoi(str[5]);
	else
		x->h_m_t_eat = -1;
	return (1);
}

void	wait_philo(t_pid *ps_kill, t_philo *lst)
{
	pid_t	ck;
	int		count;

	count = 0;
	ck = waitpid(-1, &lst -> info -> check_die, 0);
	if (WEXITSTATUS(lst -> info -> check_die) == -1)
		kill_proc(ps_kill);
	if (WEXITSTATUS(lst -> info -> check_die) == 2)
	{
		count++;
		if (count == lst -> info -> philo)
			exit(0);
	}
	if (WEXITSTATUS(lst -> info -> check_die) != 0)
		kill_proc(ps_kill);
	sem_close(lst -> info -> print);
	sem_close(lst -> info -> fork);
	destroy_semaphore();
	kill_proc(ps_kill);
}

int	main(int ac, char **av)
{
	t_var	*x;
	t_pid	*ps_kill;
	t_philo	*a;

	x = malloc(sizeof(t_var));
	a = NULL;
	if (!(ac == 6 || ac == 5))
		error_case();
	current_time();
	if (!var_init(x, av, ac) || !check_parsing(x))
		error_case();
	ph_generator(x, &a);
	while (x->j < a -> info -> philo)
	{
		x->id = fork();
		new_pid(&ps_kill, x->id);
		if (x->id == -1)
			exit(0);
		if (x->id == 0)
			philo_routine(a);
		a = a -> next;
		x->j++;
	}
	wait_philo(ps_kill, a);
}
