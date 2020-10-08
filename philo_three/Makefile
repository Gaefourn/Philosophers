NAME     =	philo_three

# 	Compiler  #
CC       =	gcc

#	Flags     #
CFLAGS   =	-Wall -Wextra -Werror 
DEBUG	 = -g3 -fsanitize=address

# 	Headers   #
HEADER_P = 	./includes
HEADER_N =	philo_three.h
HEADER   =	$(addprefix $(HEADER_P)/,$(HEADER_N))

#	Sources   #
SRC_PATH =	./srcs
TMP		 =	main.c \
			ft_utils.c \
			ft_time_and_logs.c \
		ft_moves.c

SRC_NAME =	$(TMP) $(GNL)
SRC      =	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

#	Objects   #
OBJ_PATH =	./.objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ      =	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#  Some Vars  #
DEP  = $(OBJ:%.o=%.d)
COLOR = \e[38;5;140m
RESET = \e[0m
CHECK = 0

################################################################################

all : $(NAME)
#	@sh scripts/test.sh

f : $(NAME)

#header1 :
#	@sh $(SCRIPT_P)/print_header.sh

#header2 :
#	@sh $(SCRIPT_P)/print_header2.sh


$(NAME) : header $(OBJ) bottom
	@$(CC) $(CFLAGS) $(P_LIB) $(OBJ) -o  $@ -lpthread

clear :
	@printf "\ec"

bottom :
	@printf "$(COLOR)#                                                             #\n"
	@printf "#                             \e[1;36mDONE\e[0m$(COLOR)                            #\n"
	@printf "#                                                             #\n"
	@printf "###############################################################$(RESET)\n\n"

header : clear
	@printf "$(COLOR)###############################################################\n"
	@printf "#                                                             #\n"
	@printf "#                          \e[1;36mPHILOSOPHERS\e[0m$(COLOR)                       #\n"
	@printf "#                                                             #\n"
	@printf "###############################################################$(RESET)\n"

-include $(DEP)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/$(GNL_PATH)
	@$(CC) $(CFLAGS) -MMD -I$(HEADER_P) -o $@ -c $<
	@printf "$(COLOR)#$(RESET) \e[1;30m$(CC): \e[1;37m./%-42s\e[1;0m" "$<"
	@printf "\e[32mCompiled √\e[1;0m $(COLOR)#$(RESET)\n"

debug : fclean header $(OBJ) bottom
	@$(CC) $(CFLAGS) $(DEBUG) $(P_LIB) $(OBJ) -o $@ -lpthread

clean : clear
	@rm -rf $(OBJ_PATH) 
	@printf "Cleaning files . "
	@sleep 0.5
	@printf "\rCleaning files . . "
	@sleep 0.5
	@printf "\rCleaning files . . . "
	@sleep 0.5
	@printf "\r"

save : fclean
	git add .
	git commit -m "$m"
	git push

fclean : clean
	@rm -rf $(NAME)
	@rm -rf debug

re : fclean all

.PHONY: all clean fclean re
