/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 07:58:30 by abelfany          #+#    #+#             */
/*   Updated: 2023/07/15 08:50:49 by abelfany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	new_pid(t_pid **root, int a)
{
	t_pid	*temp;
	t_pid	*ptr;

	temp = malloc(sizeof(t_pid));
	temp -> _pid = a;
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

void	kill_proc(t_pid *x)
{
	while (x)
	{
		kill(x -> _pid, SIGKILL);
		x = x -> next;
	}
}
