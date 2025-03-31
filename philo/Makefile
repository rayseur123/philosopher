NAME = philo

SRCS =  main.c \
		utils.c \
		parsing.c \
		philosopher.c \
		table_creation.c \

PATH_SRCS = src/

UTILS = obj

OBJS = $(addprefix $(UTILS)/,$(SRCS:.c=.o))
DEPS = $(addprefix $(UTILS)/,$(SRCS:.c=.d))

INCLUDE_DIRS = -Iinclude

CC = cc
CPPFLAGS += -MMD -MP $(INCLUDE_DIRS)
CFLAGS += -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ -lX11 -lXext -lm

$(UTILS)/%.o: $(PATH_SRCS)%.c | $(UTILS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<  -o $@

$(UTILS):
	@mkdir -p $(UTILS)

$(PATH_LIBS_ft): force
	$(MAKE) -C $(dir $(PATH_LIBS_ft))

$(PATH_LIBS_libx): force
	$(MAKE) -C $(dir $(PATH_LIBS_libx))

force:

-include $(DEPS)

clean:
	rm -rf $(UTILS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re