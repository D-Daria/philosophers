NAME = philo

#---mandatory part---#
OBJS_DIR = objs

SRCS_MF =	main.c ft_utils.c ft_parse_input.c\
			ft_init.c ft_philo.c ft_print.c ft_actions.c\
			ft_join_destroy.c

OBJS_M = $(addprefix $(OBJS_DIR)/, $(patsubst %.c,%.o, $(SRCS_MF)))
D_FILES_M = $(addprefix $(OBJS_DIR)/, $(patsubst %.c,%.d, $(SRCS_MF)))

INCLUDES = -I ./

#colors
RED 	= 	\033[0;31m
GREEN 	= 	\033[0;32m
BLUE	=	\033[0;34m
BREAK 	= 	\033[0m
YELLOW	=	\033[0;33m

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -pthread
SANIT_THREAD = cc -fsanitize=thread $(CFLAGS)
SANIT_ADDR = cc -fsanitize=thread $(CFLAGS)

.PHONY : all clean fclean sanit_m sanit_b re

all : $(NAME)

$(OBJS_DIR) :
	mkdir $@

$(NAME) : $(OBJS_M)
	$(CC) $(CFLAGS) $(OBJS_M) -o $(NAME)
	@echo "$(BLUE)$(NAME)$(GREEN) --> DONE!$(BREAK)"

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MD

clean :
	rm -rf $(OBJS_DIR)
	@echo "$(BLUE)objs $(RED)--> DELETED$(BREAK)"

fclean : clean
	rm -f $(NAME)
	@echo "$(BLUE)$(NAME) $(RED)--> DELETED$(BREAK)"

re : fclean all

sanit_thread :
	$(SANIT_THREAD) $(SRCS_MF) -o $(NAME)

sanit_addr :
	$(SANIT_ADDR) $(SRCS_MF) -o $(NAME)


include $(wildcard $(D_FILES_M))