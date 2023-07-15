/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:59:46 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 13:04:29 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <libc.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_var
{
	int					h_m_t_eat;
	int					check_die;
	int					die_flag;
	sem_t				*print;
	sem_t				*fork;
	int					count;
	int					philo;
	int					sleep;
	unsigned long long	time;
	int					*tab;
	int					eat;
	int					die;
	int					ac;
	pid_t				id;
	int					j;
	int					a;
}	t_var;

typedef struct s_philo
{
	unsigned long long	last_eat;
	t_var				*info;
	int					must_eat;
	int					ph_id;
	struct s_philo		*next;
}	t_philo;

typedef struct s_pid
{
	int					_pid;
	struct s_pid		*next;
}	t_pid;

unsigned long long		current_time(void);
void					check_eat_time(t_philo *a);
void					kill_proc(t_pid *x);
void					new_pid(t_pid **root, int a);
int						check_die(t_philo *a);
size_t					ft_strlen(const char *str);
void					destroy_semaphore(void);
t_philo					*link_lst(t_philo **head);
int						error_case(void);
void					_usleep(unsigned long long wait, t_philo *x);
void					routine_prainter(t_philo **creat, char *str);
unsigned long long		ge_t_ime(void);
int						ft_atoi(const char *str);
unsigned long long		current_time(void);
void					*philo_routine(t_philo	*creat);
int						check_digit(char *c);
void					ph_generator(t_var *x, t_philo **creat);

#endif
