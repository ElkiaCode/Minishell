# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 09:14:16 by cparodi           #+#    #+#              #
#    Updated: 2024/11/25 09:34:07 by cparodi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE = minishell

# Files
SRC =	srcs/main.c \
		srcs/init_struct.c \
		srcs/parsing.c \
		srcs/tokenizer.c \
		utils/split_command.c \
		utils/ft_strncpy.c \
		utils/ft_strdup.c \
		utils/tab_size.c \
		utils/ft_split_tab.c \
		utils/ft_strncmp.c \
		utils/get_token_type.c \
		utils/malloc_token.c \
		utils/union_tab.c \
		utils/ft_strcat.c \
		utils/ft_strlen.c \
		utils/search_for_args.c \
		utils/check_error.c \
		utils/expander.c \
		utils/final_parser.c \
		utils/print_test.c \
		utils/ft_strjoin.c \
		utils/get_args.c \
		utils/remove_quotes.c

SOURCES =		${SRC}
OBJECTS =		${SOURCES:.c=.o}

# Variables
CC		= cc
CFLAGS	= -Wall -Wextra -g3
LDFLAGS = -lreadline
RM		= rm -f

# Loading Bar
RESET		= \e[0m
UP			= \e[A

WHITE		= \e[0;1;97m
_WHITE		= \e[1;4;97m
RED			= \e[0;1;31m
GREEN		= \e[0;1;32m
_GREEN		= \e[1;4;32m

FILE_COUNT	= 0
FILE_TOTAL	= 23
BAR_SIZE	= ${shell expr 100 \* ${FILE_COUNT} / ${FILE_TOTAL}}
BAR_LOAD	= ${shell expr 23 \* ${FILE_COUNT} / ${FILE_TOTAL}}
BAR_REST	= ${shell expr 23 - ${BAR_LOAD}}

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
		@${CC} ${CFLAGS} ${OBJECTS} -o ${EXE} ${LDFLAGS}
		@echo "\n\n${GREEN}[✓] - ${_GREEN}Minishell${GREEN} Successfully Compiled!${RESET}"
		@${RM} ${OBJECTS}

%.o:		%.c
		@${eval FILE_COUNT = ${shell expr ${FILE_COUNT} + 1}}
		@${CC} ${CFLAGS} -c $? -o $@
		@echo "${WHITE}[!] - Compilation loading...${RESET}"
		@printf "${WHITE}[${GREEN}%-.${BAR_LOAD}s${RED}%-.${BAR_REST}s${WHITE}] [%d/%d (%d%%)]${RESET}" "#######################" "#######################" ${FILE_COUNT} ${FILE_TOTAL} ${BAR_SIZE}
		@echo ""
		@echo "${UP}${UP}${UP}"

clean:
		@${RM} ${OBJECTS}
		@echo "${WHITE}[!] - ${_WHITE}Minishell${WHITE} Successfully Cleaned!${RESET}"

fclean: clean
		@${RM} ${OBJECTS} ${EXE}
re:			fclean all

.PHONY: all clean fclean re
