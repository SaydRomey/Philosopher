# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 14:37:49 by cdumais           #+#    #+#              #
#    Updated: 2023/11/20 14:38:05 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# -------------------------------- VARIABLES --------------------------------- #
# **************************************************************************** #
NAME	:= philo
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -g




# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
PDF		:= philo_en.pdf
GIT_URL := https://github.com/SaydRomey/42_ressources
PDF_URL = $(GIT_URL)/blob/main/pdf/$(PDF)?raw=true
OS		= $(shell uname -s)

pdf:
	@curl -# -L $(PDF_URL) -o $(PDF)
ifeq ($(OS),Darwin)
	@open $(PDF)
else
	@xdg-open $(PDF) || echo "Please install a compatible PDF viewer"
endif

# @sleep 2
# @rm -f $(PDF)

.PHONY: pdf