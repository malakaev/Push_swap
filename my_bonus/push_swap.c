/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:01:24 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 15:26:10 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_glb_init(t_global *glb)
{
	glb->head_a = NULL;
	glb->head_b = NULL;
	glb->cur_a = NULL;
	glb->tail_a = NULL;
	glb->tail_b = NULL;
	glb->arr_argv = NULL;
	glb->arr_sort = NULL;
	glb->size_b = 0;
	glb->flag = 0;
	glb->prn_flag = 1;
}

int	main(int argc, char **argv)
{
	int			i;
	t_global	*glb;

	glb = NULL;
	if (argc < 2)
		ft_exit(0, glb);
	glb = (t_global *)malloc(sizeof(t_global));
	if (glb == NULL)
		ft_exit(4, glb);
	ft_glb_init(glb);
	glb->ttl_size = argc - 1;
	glb->size_a = glb->ttl_size;
	ft_argv_to_array(glb, argv);
	glb->head_a = ft_stk_init(glb->arr_argv[0], glb);
	glb->cur_a = glb->head_a;
	i = 1;
	while (i < glb->ttl_size)
	{
		glb->cur_a = ft_stk_add_el(glb->cur_a, glb->arr_argv[i], glb);
		i++;
	}
	ft_stack_sort(glb);
	ft_sort_final(glb);
	ft_exit(0, glb);
}
