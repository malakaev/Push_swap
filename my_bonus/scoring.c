/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:10:34 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/09 18:34:32 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_score_part2(t_stack *cur_b, int sc_sum[])
{
	int	i;
	int	min;

	i = 1;
	min = sc_sum[0];
	cur_b->var = 0;
	cur_b->score = min;
	while (i < 4)
	{
		if (min > sc_sum[i])
		{
			min = sc_sum[i];
			cur_b->var = i;
			cur_b->score = min;
		}
		i++;
	}
}

t_stack	*ft_score_part1(t_stack *cur_b, t_global *glb, t_score s)
{
	t_stack	*cur_a;
	int		sc_sum[4];

	s.b2 = glb->size_b - s.b1;
	cur_a = glb->head_a;
	s.a1 = 0;
	while ((cur_a != glb->head_a || s.a1 == 0) && \
		(cur_b->el > cur_a->el || cur_b->el < cur_a->prv->el))
	{
		s.a1++;
		cur_a = cur_a->nxt;
	}
	s.a2 = glb->size_a - s.a1;
	if (s.b1 > s.a1)
		sc_sum[0] = s.b1;
	else
		sc_sum[0] = s.a1;
	if (s.b2 > s.a2)
		sc_sum[3] = s.b2;
	else
		sc_sum[3] = s.a2;
	sc_sum[1] = s.b1 + s.a2;
	sc_sum[2] = s.b2 + s.a1;
	ft_score_part2(cur_b, sc_sum);
	return (cur_a);
}

void	ft_scoring_main(t_global *glb)
{
	t_stack	*cur_a;
	t_stack	*cur_b;
	t_score	s;

	cur_b = glb->head_b;
	s.b1 = 0;
	while (cur_b != glb->head_b || s.b1 == 0)
	{
		cur_a = ft_score_part1(cur_b, glb, s);
		if (s.b1 == 0)
		{
			glb->min_score = cur_b->score;
			glb->to_push = cur_b;
			glb->place = cur_a;
		}
		if (glb->min_score > cur_b->score)
		{
			glb->min_score = cur_b->score;
			glb->to_push = cur_b;
			glb->place = cur_a;
		}
		cur_b = cur_b->nxt;
		s.b1++;
	}
}
