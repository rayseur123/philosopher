NAME := philo

# --- SRC/DIR --- #

SRC_DIR := src/

SRCS :=	main.c 		 		   	  \
					utils.c        \
					parsing.c       \
					philosopher.c    \
					table_creation.c  \
					manage_pack_data.c \
					do_philo.c		    \
					utils_to_threads.c 	 \
					manage_must_eat.c 	  \
					manage_fork.c 		   \


# --- LIBS TARGET --- #

LIBS_TARGET :=

LIBS :=

# --- INCLUDES --- #

INCLUDES := includes/

# --- OBJS/DEPS --- #

OBJS_DIR := .build/objs/

OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))


DEPS := $(OBJS:.o=.d)

# --- FLAGS --- #

CPPFLAGS += -MMD -MP $(addprefix -I,$(INCLUDES)) \
					 $(addprefix -I,$(addsuffix $(INCLUDES),$(dir $(LIBS_TARGET))))

CFLAGS += -Wall -Wextra -Werror -g3

LFLAGS += 	$(addprefix -L,$(dir $(LIBS_TARGET))) \
			$(addprefix -l,$(LIBS)) \
			

# --- COMPILATER --- #

CC = cc

# --- EXEC --- #

all : $(NAME)

$(NAME) : $(LIBS_TARGET) $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBS_TARGET) : force
	$(MAKE) -C $(dir $@)

force:

.PHONY : clean fclean all re print-% debug force

clean:
	rm -rf .build

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug: $(NAME)
	valgrind --tool=helgrind ./$(NAME) 5 400 200 200

print-%:
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

-include $(DEPS)
