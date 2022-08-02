
#* TARGET *#
TARGET = minishell

#*SOURCE FILES *#
PARSING = minishell.c parser.c utils.c utils_2.c utils_3.c init_nodes.c
EXEC = exec.c path.c list.c
SRC = $(addprefix parsing/, $(PARSING)) \
	  $(addprefix execution/, $(EXEC))

#* OBJECT FILES *#
OBJS = $(SRC:%.c=%.o)

#* FLAGS *#
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

#* HEADER FILES *#
INCLUDE = include/

#* DELETE *#
DEL = rm -f

all: $(TARGET)

%.o: %.c
	cc $(FLAGS) -c -I $(INCLUDE) $< -o $@

$(TARGET): $(OBJS) $(INCLUDE)
	cc $(FLAGS) -I $(INCLUDE) -lreadline $(OBJS) -o $(TARGET)
#$(CC) $(CFLAGS) $(SRCS) -w -DMEMWATCH -DMW_STDIO memwatch-2.71/memwatch.c  -o push_swap && rm -rf memwatch.log

re: fclean all

clean:
	$(DEL) $(OBJS)

fclean:	clean
	$(DEL) $(TARGET)

.PHONY: clean fclean re all