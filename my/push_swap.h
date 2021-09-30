#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h> //for write, read
# include <stdlib.h> //for malloc, free
# include <fcntl.h> //for open

typedef struct s_stack_a
{
	struct s_stack_a	*prev;
	struct s_stack_a	*next;
	int					el;
	int					idx;
	int					size;
}						t_stack_a;


#endif
