# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 14:37:49 by cdumais           #+#    #+#              #
#    Updated: 2023/11/23 10:42:03 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# https://nafuka11.github.io/philosophers-visualizer/
# **************************************************************************** #
# -------------------------------- VARIABLES --------------------------------- #
# **************************************************************************** #
NAME	:= philo

# number of philosophers
ARG_1	:= 4
# time to die
ARG_2	:= 800
# time to eat
ARG_3	:= 200
# time to sleep
ARG_4	:= 200
# number of times each philosopher must eat
ARG_5	:= 7

ARGS	:= $(ARG_1) $(ARG_2) $(ARG_3) $(ARG_4) $(ARG_5)


INC_DIR	:= inc
OBJ_DIR	:= obj
SRC_DIR	:= src
TMP_DIR	:= tmp

COMPILE	:= gcc
C_FLAGS	:= -Wall -Wextra -Werror
L_FLAGS	:= -lpthread
HEADERS	:= -I$(INC_DIR)

REMOVE	:= rm -rf
OS		:= $(shell uname -s)

ifeq ($(OS),Linux)
	C_FLAGS += $(L_FLAGS)
endif
# **************************************************************************** #
# -------------------------------- ALL * FILES ------------------------------- #
# **************************************************************************** #
INCS	:=	$(wildcard $(INC_DIR)/*.h)
SRCS	:=	$(wildcard $(SRC_DIR)/*.c)
OBJS	:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
# SRC		:=
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
# INC		:=
# **************************************************************************** #
# -------------------------------- ALL FILES --------------------------------- #
# **************************************************************************** #
# INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
# SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
# OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(OBJS)
	@$(COMPILE) $(C_FLAGS) $(OBJS) -o $@
	@echo "$@ is ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(REMOVE) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@$(REMOVE) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
run: $(NAME)
	@./$(NAME) $(ARGS)

leaks: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS)

assembly: $(NAME) | $(TMP_DIR)
	@$(COMPILE) $(C_FLAGS) -S $(SRCS) $(HEADERS)
	@mv *.s $(TMP_DIR)
	@echo "Assembly files created in $(TMP_DIR)"

$(TMP_DIR):
	@mkdir -p $(TMP_DIR)

ffclean: fclean
	@$(REMOVE) $(TMP_DIR)

.PHONY: run assembly ffclean
# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
PDF		:= philo_en.pdf
GIT_URL := https://github.com/SaydRomey/42_ressources
PDF_URL = $(GIT_URL)/blob/main/pdf/$(PDF)?raw=true

pdf: | $(TMP_DIR)
	@curl -# -L $(PDF_URL) -o $(TMP_DIR)/$(PDF)
ifeq ($(OS),Darwin)
	@open $(TMP_DIR)/$(PDF)
else
	@xdg-open $(TMP_DIR)/$(PDF) || echo "Please install a compatible PDF viewer"
endif

.PHONY: pdf
# **************************************************************************** #
