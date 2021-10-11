/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/11 20:38:51 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_exit(int code, t_global *glb)
{
	t_stack	*tmp;
	t_stack	*cur;

	if (code != 0)
	{
		cur = glb->tail_a;
		while (cur != NULL && cur != glb->head_a)
		{
			tmp = cur;
			cur = cur->prv;
			free(tmp);
			tmp = NULL;
		}
		free(glb->head_a);
		free(glb->arr_sort);
		free(glb->arr_argv);
		free(glb);
		write(1, "Error\n", 6);
		exit (EXIT_FAILURE);
	}
	exit (EXIT_SUCCESS);
}

void	ft_exit_2(t_global *glb)
{
	free(glb->head_a);
	free(glb->head_b);
	free(glb->arr_sort);
	free(glb->arr_argv);
	free(glb);
	write(1, "KO\n", 3);
	exit (EXIT_FAILURE);
}

void	ft_exit_free_stack(t_global *glb)
{
	t_stack	*tmp;
	t_stack	*cur;

	cur = glb->tail_a;
	while (cur != NULL && cur != glb->head_a)
	{
		write(1, "ex1\n", 4);
		tmp = cur;
		cur = cur->prv;
		free(tmp);
		tmp = NULL;
	}
	cur = glb->tail_b;
	while (cur != NULL && cur != glb->head_b)
	{
		write(1, "ex2\n", 4);
		tmp = cur;
		cur = cur->prv;
		free(tmp);
		tmp = NULL;
	}
}

void	ft_exit_ok(int code, t_global *glb)
{
	if (code != 0)
	{
		ft_exit_free_stack(glb);
		ft_exit_2(glb);
	}
	write(1, "OK\n", 3);
	exit (EXIT_SUCCESS);
}
