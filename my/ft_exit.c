/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/09 18:13:01 by kgolda           ###   ########.fr       */
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
