NAME = philo_bonus

#---bonus part---#
OBJS_B_DIR = objs_bonus

SRCS_BF =	main_bonus.c ft_utils_bonus.c\
			ft_parse_input_bonus.c ft_init_bonus.c\
			ft_philo_bonus.c ft_print_bonus.c\
			ft_actions_bonus.c ft_itoa.c

OBJS_B = $(addprefix $(OBJS_B_DIR)/, $(patsubst %.c,%.o, $(SRCS_BF)))
D_FILES_B = $(addprefix $(OBJS_B_DIR)/, $(patsubst %.c,%.d, $(SRCS_BF)))

INCLUDES_B = -I ./

#colors
RED 	= 	\033[0;31m
GREEN 	= 	\033[0;32m
BLUE	=	\033[0;34m
BREAK 	= 	\033[0m
YELLOW	=	\033[0;33m

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -pthread
SANIT_THREAD = cc $(CFLAGS) -fsanitize=thread
SANIT_ADDR = cc $(CFLAGS) -fsanitize=thread

.PHONY : all clean fclean sanit_m sanit_b re

all : $(NAME)

$(OBJS_B_DIR) :
	mkdir $@

$(NAME) : $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME)
	@echo "$(BLUE)$(NAME)$(GREEN) --> DONE!$(BREAK)"

$(OBJS_B_DIR)/%.o : %.c | $(OBJS_B_DIR)
	$(CC) $(CFLAGS) $(INCLUDES_B) -c $< -o $@ -MD

clean :
	rm -rf $(OBJS_B_DIR)
	@echo "$(BLUE)objs $(RED)--> DELETED$(BREAK)"

fclean : clean
	rm -f $(NAME)
	@echo "$(BLUE)$(NAME) $(RED)--> DELETED$(BREAK)"

re : fclean all

sanit_thread : $(OBJS_B)
	$(SANIT_THREAD) $(SRCS_BF) -o $(NAME)

sanit_addr : $(OBJS_B)
	$(SANIT_ADDR) $(SRCS_BF) -o $(NAME)

include $(wildcard $(D_FILES_B))