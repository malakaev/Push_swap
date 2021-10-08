#include <stdio.h> //for printf
#include <unistd.h> //for write, read (ssize_t read(int fildes, void *buf, size_t nbyte);)
#include <stdlib.h> //for malloc, free, exit
#include <fcntl.h> //for open
#include <limits.h> //for open
//#include "push_swap.h"

typedef struct s_stack
{
	struct s_stack	*prv;
	struct s_stack	*nxt;
	int				el;
	int				score;
	int				var;
}					t_stack;

typedef struct s_global //структура для хранения общих данных
{
	t_stack	*head_a; //корень стека А
	t_stack	*head_b;
	t_stack	*cur_a; //текущий узел
	t_stack	*cur_b; //текущий узел - вроде не нужен
	t_stack	*tail_a; //конец стека А
	t_stack	*tail_b;
	int		size_a;
	int		size_b;
	int		ttl_size;
	long	max;
	long	min;
	long	mid;
	long	*arr_argv; //массив значений полученный из аргументов (из argv)
	long	*arr_sort; //отсортированный массив значений
}			t_global;

typedef struct s_score
{
	int				a1;
	int				a2;
	int				b1;
	int				b2;
}					t_score;

void	ft_exit (int code, t_global *glb)
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

long	ft_atoi(const char *s, t_global *glb)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	sign = 1;
	while (s[i] && ((s[i] == 32) || ((s[i] > 8) && (s[i] < 14)))) //пропуск разных пробелов
		i++;
	if (s[i] == 45) //если есть минус
	{
		sign = -1;
		i++;
	}
	else
		if (s[i] == 43) //если есть +
			i++;
	if (s[i] == '\0' || s[i] == 32 || ((s[i] > 8) && (s[i] < 14)))
		ft_exit (2, glb);
	res = 0;
	while ((s[i] > 47) && (s[i] < 58))
		res = (s[i++] - 48) + res * 10;
	if (s[i] != '\0' && s[i] != 32 && ((s[i] < 9) || (s[i] > 13)))
		ft_exit (2, glb);
	return ((long)(res * sign));
}

t_stack	*ft_stk_add_el(t_stack *stk_cur, int data, t_global *glb) //stk_cur указатель на текущий узел, т.е. на тот после которого мы вставляем новый узел и он станет предыдущим prv
{
	t_stack	*new; //указатель на новый узел
	t_stack	*tmp_nxt; //указатель на след узел stk_cur->next

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

t_stack	*ft_stk_init(int data, t_global *glb) //(s_stack_a	*prev, t_stack_a *next, int el, int	idx, int size) здесь буду записывать значения из argv в стек А
{
	t_stack	*stk_init;

	stk_init = (t_stack *)malloc(sizeof(t_stack));
	if (stk_init == NULL)
		ft_exit(5, glb);
	stk_init->el = data;
	stk_init->nxt = stk_init;
	stk_init->prv = stk_init;
	return (stk_init); //указатель на корень списка
}

void	ft_sort_arr(long *mass, int n)
{
	int	i;
	int	j;
	long	tmp;
	long	min_pos;

	i = 0;
	while (i < n)
	{
		min_pos = i;
		j = i + 1;
		while (j < n)
		{
			if (mass[min_pos] > mass[j])
				min_pos = j;
			j++;
		}
		tmp = mass[min_pos];
		mass[min_pos] = mass[i];
		mass[i] = tmp;
		i++;
	}
}

//Проверка на дубликаты и отсортированность
void	ft_check(t_global *glb)
{
	int	i;
	int	sorted;

	i = 0;
	sorted = 1;
	while (i < glb->ttl_size) //проверка сортировки
	{
		if (glb->arr_argv[i] != glb->arr_sort[i])
			sorted = 0; //значит не отсортирован т.е. ОК
		if (i + 1 < glb->ttl_size)
			if (glb->arr_sort[i] == glb->arr_sort[i + 1]) //значит есть дубли - НЕОК
				ft_exit(2, glb);
		i++;
	}
	if (sorted == 1)
		ft_exit(0, glb);
	if (glb->max > INT_MAX || glb->min < INT_MIN)
		ft_exit(2, glb);
}


void	ft_argv_to_array(t_global *glb, char **argv) //1.3 Поместить в другой массив для анализа? или в список
{
	int		i;

	glb->arr_argv = (long *)malloc(sizeof(long) * glb->ttl_size);
	glb->arr_sort = (long *)malloc(sizeof(long) * glb->ttl_size);
	if (glb->arr_argv == NULL || glb->arr_sort == NULL)
		ft_exit(5, glb);
	i = 0;
	while (i < glb->ttl_size)
	{
		glb->arr_argv[i] = ft_atoi(argv[i + 1], glb);
		glb->arr_sort[i] = glb->arr_argv[i];
		i++;
	}
	ft_sort_arr(glb->arr_sort, glb->ttl_size);
	glb->min = glb->arr_sort[0];
	glb->max = glb->arr_sort[glb->ttl_size - 1];
	glb->mid = glb->arr_sort[glb->ttl_size/2];
	ft_check(glb);
}

/* ОПЕРАЦИИ СО СТЕКОМ */

void	ft_sa(t_global *glb)
{
	t_stack	*tmp;

	if (glb->size_a < 2)
		return ;
	tmp = glb->head_a->nxt;
	tmp->prv = glb->tail_a;
	glb->head_a->prv = tmp;
	glb->head_a->nxt = tmp->nxt;
	tmp->nxt->prv = glb->head_a;
	tmp->nxt = glb->head_a;
	glb->head_a = tmp;
	glb->tail_a->nxt = glb->head_a;
	write(1, "sa\n", 3);
}

void	ft_pb(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_a;
	glb->head_a = glb->head_a->nxt;
	glb->head_a->prv = glb->tail_a;
	glb->tail_a->nxt = glb->head_a;
	if (glb->size_b == 0)
	{
		tmp->nxt = tmp;
		tmp->prv = tmp;
		glb->head_b = tmp;
		glb->tail_b = tmp;
	}
	else
	{
		tmp->nxt = glb->head_b;
		glb->head_b->prv = tmp;
		tmp->prv = glb->tail_b;
		glb->tail_b->nxt = tmp;
		glb->head_b = tmp;
	}
	(glb->size_a)--;
	(glb->size_b)++;
	write(1, "pb\n", 3);
}

void	ft_pa(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_b;
	if (glb->size_b > 1)
	{
		glb->head_b = glb->head_b->nxt;
		glb->head_b->prv = glb->tail_b;
		glb->tail_b->nxt = glb->head_b;
	}
	else
	{
		glb->head_b = NULL;
		glb->tail_b = NULL;
	}
	tmp->nxt = glb->head_a;
	glb->head_a->prv = tmp;
	tmp->prv = glb->tail_a;
	glb->tail_a->nxt = tmp;
	glb->head_a = tmp;
	(glb->size_a)++;
	(glb->size_b)--;
	write(1, "pa\n", 3);
}

void	ft_ra(t_global *glb)
{
	glb->head_a = glb->head_a->nxt;
	glb->tail_a = glb->tail_a->nxt;
	write(1, "ra\n", 3);
}

void	ft_rra(t_global *glb)
{
	glb->head_a = glb->head_a->prv;
	glb->tail_a = glb->tail_a->prv;
	write(1, "rra\n", 4);
}

void	ft_rb(t_global *glb)
{
	glb->head_b = glb->head_b->nxt;
	glb->tail_b = glb->tail_b->nxt;
	write(1, "rb\n", 3);
}

void	ft_rrb(t_global *glb)
{
	glb->head_b = glb->head_b->prv;
	glb->tail_b = glb->tail_b->prv;
	write(1, "rrb\n", 4);
}

void	ft_rr(t_global *glb)
{
	glb->head_a = glb->head_a->nxt;
	glb->tail_a = glb->tail_a->nxt;
	glb->head_b = glb->head_b->nxt;
	glb->tail_b = glb->tail_b->nxt;
	write(1, "rr\n", 3);
}

void	ft_rrr(t_global *glb)
{
	glb->head_a = glb->head_a->prv;
	glb->tail_a = glb->tail_a->prv;
	glb->head_b = glb->head_b->prv;
	glb->tail_b = glb->tail_b->prv;
	write(1, "rrr\n", 4);
}

void	ft_sort_final(t_global *glb)
{
	int	i;
	t_stack *tmp;

	i = 0;
	tmp = glb->head_a;
	while (tmp->el != glb->min)
		{
			tmp = tmp->nxt;
			i++;
		}
	if (i > (glb->size_a - i))
		while (glb->head_a->el != glb->min)
			ft_rra(glb);
	else
		while (glb->head_a->el != glb->min)
			ft_ra(glb);
}
//Предсортировка стека А в котором осталось 3 узла
void	ft_predsort_a(t_global *glb)
{
	t_stack	*tmp;

	tmp = glb->head_a;
	while (tmp->el != glb->max)
		tmp = tmp->nxt;
	if (tmp->nxt->el == glb->mid)
		ft_sa(glb);
}

//ПУШ из Б в А
void	ft_sort_push_var03(t_stack *to_push, t_stack *place, t_global *glb)
{
	if (to_push->var == 0)
	{
		while (glb->head_b != to_push && glb->head_a != place)
			ft_rr(glb);
		while (glb->head_b != to_push)
			ft_rb(glb);
		while (glb->head_a != place)
			ft_ra(glb);
	}
	if (to_push->var == 3)
	{
		while (glb->head_b != to_push && glb->head_a != place)
			ft_rrr(glb);
		while (glb->head_b != to_push)
			ft_rrb(glb);
		while (glb->head_a != place)
			ft_rra(glb);
	}
}

void	ft_sort_push(t_stack *to_push, t_stack *place, t_global *glb)
{
	if (to_push->var == 0)
		ft_sort_push_var03(to_push, place, glb);
	if (to_push->var == 1)
	{
		while (glb->head_b != to_push)
			ft_rb(glb);
		while (glb->head_a != place)
			ft_rra(glb);
	}
	if (to_push->var == 2)
	{
		while (glb->head_b != to_push)
			ft_rrb(glb);
		while (glb->head_a != place)
			ft_ra(glb);
	}
	if (to_push->var == 3)
		ft_sort_push_var03(to_push, place, glb);
	ft_pa(glb);
}

//СКОРИНГ эл-в стека B если size_b > 1

void	ft_score_part2(t_stack *cur_b, int sc_sum[])
{
	int	i;
	int	min;
	//int	sc_sum[4];

	i = 1;
	min = sc_sum[0]; //находим минимальный score и вариант для сортировки
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
	while ((cur_a != glb->head_a || s.a1 == 0) &&
	(cur_b->el > cur_a->el || cur_b->el < cur_a->prv->el))//ДОБавить условие если b < a
	{
		s.a1++;
		cur_a = cur_a->nxt;
	}
	s.a2 = glb->size_a - s.a1;
	if (s.b1 > s.a1) //итоговый score для элемента
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
	t_stack	*to_push;
	t_stack	*place;
	int		min_score;
	t_score	s;

	cur_b = glb->head_b;
	s.b1 = 0;
	while (cur_b != glb->head_b || s.b1 == 0)
	{
		cur_a = ft_score_part1(cur_b, glb, s);
		if (cur_b->score == 0) //Если score == 0 то нет смысла дальше делать скоринг
		{
			to_push = cur_b;
			place = cur_a;
			break;
		}
		if (s.b1 == 0) //поиск узла с минимальным score
		{
			min_score = cur_b->score;
			to_push = cur_b;
			place = cur_a;
		}
		if (min_score > cur_b->score)
		{
			min_score = cur_b->score;
			to_push = cur_b;
			place = cur_a;
		}
		cur_b = cur_b->nxt;
		s.b1++;
	}
	ft_sort_push(to_push, place, glb);
}

void	ft_stack_sort(t_global *glb)
{
	int		flag = 0;

	glb->size_b = 0;
	glb->head_b = NULL;
	while (glb->size_a > 3)
		if (glb->head_a->el != glb->min &&
		glb->head_a->el != glb->max && glb->head_a->el != glb->mid)
			if (glb->head_a->el < glb->mid && flag == 1) //&& glb->size_b > 2)
			{
				ft_pb(glb);
				ft_rb(glb);
			}
			else
			{
				ft_pb(glb);
				flag = 1; //условие чтобы rb делать только если эл-т > mid уже попал в стек B
			}
		else
			ft_ra(glb);
	ft_predsort_a(glb);
	while (glb->size_b > 0) //скоринг эл-в стека B
		ft_scoring_main(glb);
	ft_sort_final(glb); //финальная прокрутка стека А для законченной сортировки
}

void	ft_glb_init(t_global *glb)
{
	glb->head_a = NULL;
	glb->head_b = NULL;
	glb->cur_a = NULL;
	glb->cur_b = NULL;
	glb->tail_a = NULL;
	glb->tail_b = NULL;
	glb->arr_argv = NULL;
	glb->arr_sort = NULL;
}

int	main(int argc, char **argv)
{
	int			i;
	t_global	*glb; //хранит указатели на корни списков и текущие узлы, и общие данные

	glb = NULL;
	if (argc < 2)
		ft_exit(0, glb); // добавить - если argc = 2 то прогнать argv[1] через split на случай если подали аргументы в кавычках "1 3 6 2 4" и отправить на проверку валидности
	glb = (t_global *)malloc(sizeof(t_global));
	if (glb == NULL)
		ft_exit(4, glb);
	ft_glb_init(glb);
	glb->ttl_size = argc - 1;
	glb->size_a = glb->ttl_size;
	ft_argv_to_array(glb, argv);
	glb->head_a = ft_stk_init(glb->arr_argv[0], glb); //инициализация стека А создание корневого элемента - узла
	//glb->tail_a = glb->head_a; //на случай если 1 арг-т, возможно не нужно
	glb->cur_a = glb->head_a; // копирование эл-в в стек А
	i = 1;
	while (i < glb->ttl_size)
	{
		glb->cur_a  = ft_stk_add_el(glb->cur_a, glb->arr_argv[i], glb); //копирование элементов из массива в стек А
		i++;
	}
	ft_stack_sort(glb); //функция работы со стеками
	ft_exit(0, glb);
}
