/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:59:46 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 17:03:33 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <libc.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_var
{
	int					ac;
	unsigned long long	time;
	pthread_mutex_t		update;
	pthread_mutex_t		print;
	pthread_mutex_t		died;
	pthread_mutex_t		mute;
	int					h_m_t_eat;
	int					philo;
	int					sleep;
	int					*tab;
	int					eat;
	int					die;
	int					count;
	int					gg;
	int					kk;
	int					j;
}	t_var;

typedef struct s_philo
{
	unsigned long long	last_eat;
	pthread_mutex_t		fork;
	t_var				*info;
	int					must_eat;
	int					ph_id;
	struct s_philo		*next;
}	t_philo;

unsigned long long		current_time(void);
size_t					ft_strlen(const char *str);
void					destroy_mutex(t_philo **dest);
t_philo					*link_lst(t_philo **head);
int						error_case(void);
void					_usleep(unsigned long long wait);
void					routine_prainter(t_philo **creat, char *str);
unsigned long long		ge_t_ime(void);
int						ft_atoi(const char *str);
unsigned long long		current_time(void);
void					*philo_routine(void *x);
int						check_digit(char *c);
void					ph_generator(t_var *x, t_philo **creat);

#endif
