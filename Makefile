NAME 			= pipex
NAME_BONUS		= pipex_bonus

GREEN           = \033[0;32m
RED             = \033[0;31m
RESET           = \033[0m

INCLUDES_DIRS	= -I./libraries/Libft  -I./include
LIBFT           = ./libraries/Libft/libft.a
CC = cc
INCLUDE_DIRS    = -I./libraries/Libft
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES_DIRS)

SRCS_DIR        = ./sources/
BONUS_SRCS_DIR  = ./bonus_sources/

SRCS 			= $(addprefix $(SRCS_DIR),			\
				pipex.c  							\
				free_close_message.c				\
				find_executable.c					\
				check_files.c						\
				execute_command.c)
				
SRCS_BONUS      = $(addprefix $(BONUS_SRCS_DIR), 	\
				pipex_bonus.c  						\
				create_pipes_bonus.c					\
				free_close_message_bonus.c			\
				find_executable_bonus.c				\
				check_files_bonus.c					\
				execute_command_bonus.c)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

REMOVE = rm -f

all: 			${LIBFT} $(NAME)

$(NAME): 		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INCLUDES_DIRS)
				@echo "$(NAME): $(GREEN)$(NAME) was compiled.$(RESET)"
				@echo

bonus:			$(OBJS_BONUS)
				@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS) $(INCLUDES_DIRS)
				@echo "$(NAME_BONUS): $(GREEN)$(NAME_BONUS) was compiled.$(RESET)"
				@echo

%.o: %.c		
				$(CC) $(CFLAGS) -c $< -o $@
# @echo "\n$(NAME): $(GREEN)object files were created$(RESET)"   

${LIBFT}:
				@echo
				make bonus -C libraries/Libft

clean:
				make clean -C libraries/Libft
				${REMOVE} $(OBJS) 
				${REMOVE} $(OBJS_BONUS)
				@echo "\n${NAME}: $(RED)object files were deleted$(RESET)"


fclean: 		clean
				${REMOVE} ${NAME} ${NAME_BONUS} ${LIBFT}
				@echo "${NAME}: ${RED} ${LIBFT} ${NAME} and ${NAME_BONUS} were deleted${RESET}"
				@echo

re: 			fclean all

# 声明伪目标
.PHONY: all clean fclean re bonus
