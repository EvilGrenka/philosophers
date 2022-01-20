# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnoriko <rnoriko@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 13:42:16 by rnoriko           #+#    #+#              #
#    Updated: 2022/01/20 03:02:32 by rnoriko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus

CC = clang
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -rf

INC_DIR = philo/includes
SRC_DIR = philo/sources
OBJ_DIR = philo/objects
ROOT_FOLDER = philo/

INC_DIR_BONUS = philo_bonus/includes
SRC_DIR_BONUS = philo_bonus/sources
OBJ_DIR_BONUS = philo_bonus/objects
ROOT_FOLDER_BONUS = philo_bonus/

HEADERS = $(wildcard $(INC_DIR)/*.h)
SRCS	= $(wildcard $(SRC_DIR)/*.c)
vpath %.c $(SRC_DIR)
OBJS	= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADERS_BONUS = $(wildcard $(INC_DIR_BONUS)/*.h)
SRCS_BONUS	= $(wildcard $(SRC_DIR_BONUS)/*.c)
vpath %.c $(SRC_DIR_BONUS)
OBJS_BONUS	= $(addprefix $(OBJ_DIR_BONUS)/, $(notdir $(SRCS_BONUS:.c=.o)))

all : $(NAME)

bonus: $(NAME_BONUS)

clean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_DIR_BONUS)
	@printf "🧹 Cleaning $(NAME)'s Object files...\n"

fclean : clean
	@$(RM) $(RMFLAGS) $(addprefix $(ROOT_FOLDER)/, $(NAME))
	@$(RM) $(RMFLAGS) $(addprefix $(ROOT_FOLDER_BONUS)/, $(NAME_BONUS))
	@printf "🧹 Cleaning $(NAME)\n"

re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(HEADERS) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR)  -c $< -o $@
	@printf "🔮 Create $@ from $<\n"

$(NAME) : $(HEADERS) $(OBJS)
	@printf "🪧 Successfully Created $@'s Object files!\n"
	@printf "📜 Create $@!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) -o $(addprefix $(ROOT_FOLDER)/, $(NAME))
	@printf "🧶 Successfully Created $@!\n"

$(OBJ_DIR_BONUS) :
	@mkdir $(OBJ_DIR_BONUS)

$(OBJ_DIR_BONUS)/%.o : %.c $(OBJ_DIR_BONUS) $(HEADERS_BONUS)
	@$(CC) $(CFLAGS) -I $(INC_DIR_BONUS) -c $< -o $@
	@printf "🔮 Create $@ from $<\n"

$(NAME_BONUS) : $(HEADERS_BONUS) $(OBJS_BONUS)
	@printf "🪧 Successfully Created $@'s Object files!\n"
	@printf "📜 Create $@!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR_BONUS) $(OBJS_BONUS) -o $(addprefix $(ROOT_FOLDER_BONUS)/, $(NAME_BONUS))
	@printf "🧶 Successfully Created $@!\n"

PHONY: all bonus clean fclean re