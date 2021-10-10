/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:46:15 by kgolda            #+#    #+#             */
/*   Updated: 2021/10/10 20:15:11 by kgolda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h> //for write
# include <stdlib.h> //for malloc, free, exit
# include <limits.h> //for INT_MAX INT_MIN

typedef struct s_stack
{
	struct s_stack	*prv;
	struct s_stack	*nxt;
	int				el;
	int				score;
	int				var;
}					t_stack;

typedef struct s_global
{
	t_stack	*head_a;
	t_stack	*head_b;
	t_stack	*cur_a;
	t_stack	*tail_a;
	t_stack	*tail_b;
	t_stack	*to_push;
	t_stack	*place;
	int		size_a;
	int		size_b;
	int		ttl_size;
	int		flag;
	int		prn_flag;
	long	max;
	long	min;
	long	mid;
	int		min_score;
	long	*arr_argv;
	long	*arr_sort;
}			t_global;

typedef struct s_score
{
	int	a1;
	int	a2;
	int	b1;
	int	b2;
}		t_score;

void	ft_exit(int code, t_global *glb);
long	ft_atoi(const char *s, t_global *glb);
t_stack	*ft_stk_add_el(t_stack *stk_cur, int data, t_global *glb);
t_stack	*ft_stk_init(int data, t_global *glb);
void	ft_sort_arr(long *mass, int n);
void	ft_check(t_global *glb);
void	ft_argv_to_array(t_global *glb, char **argv);
void	ft_sa(t_global *glb);
//void	ft_sb(t_global *glb);
//void	ft_ss(t_global *glb);
void	ft_pb(t_global *glb);
void	ft_pa(t_global *glb);
void	ft_ra(t_global *glb);
void	ft_rra(t_global *glb);
void	ft_rb(t_global *glb);
void	ft_rrb(t_global *glb);
void	ft_rr(t_global *glb);
void	ft_rrr(t_global *glb);
void	ft_sort_final(t_global *glb);
void	ft_predsort_a(t_global *glb);
void	ft_sort_push_var03(t_global *glb);
void	ft_sort_push(t_global *glb);
void	ft_score_part2(t_stack *cur_b, int sc_sum[]);
t_stack	*ft_score_part1(t_stack *cur_b, t_global *glb, t_score s);
void	ft_scoring_main(t_global *glb);
void	ft_stack_sort(t_global *glb);
void	ft_glb_init(t_global *glb);

//for bonus
void	ft_exit_OK(int code, t_global *glb);
void	ftb_sa(t_global *glb);
void	ftb_sb(t_global *glb);
void	ftb_ss(t_global *glb);
void	ftb_pb(t_global *glb);
void	ftb_pa(t_global *glb);
int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *str1, const char *str2, size_t len);
void	ftb_compare(char *line, t_global *glb, size_t len);
void	ftb_pars_commands(t_global *glb);
void	ftb_check_sort_stack(t_global *glb);

#endif
