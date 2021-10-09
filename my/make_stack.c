/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/09 20:17:45 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_stk_add_el(t_stack *stk_cur, int data, t_global *glb)
{
	t_stack	*new;
	t_stack	*tmp_nxt;

	tmp_nxt = stk_cur->nxt;
	new = (t_stack *)malloc(sizeof(t_stack));
	if (new == NULL)
		ft_exit(5, glb);
	stk_cur->nxt = new;
	new->el = data;
	new->nxt = tmp_nxt;
	new->prv = stk_cur;
	glb->tail_a = new;
	glb->head_a->prv = new;
	return (new);
}

t_stack	*ft_stk_init(int data, t_global *glb)
{
	t_stack	*stk_init;

	stk_init = (t_stack *)malloc(sizeof(t_stack));
	if (stk_init == NULL)
		ft_exit(5, glb);
	stk_init->el = data;
	stk_init->nxt = stk_init;
	stk_init->prv = stk_init;
	return (stk_init);
}
