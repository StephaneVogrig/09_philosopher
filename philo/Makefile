# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 19:41:13 by stephane          #+#    #+#              #
#    Updated: 2024/06/19 16:05:15 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo
NAME_DEBUG	:=	$(NAME)_debug
NAME_SAN	:=	$(NAME)_sanitize

# sources ---------------------------------------------------------------------#

DIR_SRC		:=	src
SRC			:=	main.c \
				arg.c \
				exit.c

SRC			:=	$(SRC:%=$(DIR_SRC)/%)

# includes --------------------------------------------------------------------#

DIR_INC		:=	include
I_FLAG		:=	$(addprefix -I,$(DIR_INC)) -MMD -MP
				
# objects ---------------------------------------------------------------------#

DIR_BUILD	:=	.build
OBJ			:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_DEBUG	:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/debug/%.o)
OBJ_SAN		:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)

DEPS		:=	$(OBJ:.o=.d) $(OBJ_SAN:.o=.d) $(OBJ_BONUS:.o=.d)

# compilation -----------------------------------------------------------------#

CC			:=	cc
CC_FLAGS	:=	-Wall -Wextra -Werror

VAL_FLAGS	:=	--leak-check=full --track-origins=yes --track-fds=yes
VAL_FLAGS_C	:=	--show-leak-kinds=all --trace-children=yes

SAN_FLAGS	:=	-fsanitize=address -g

# make ------------------------------------------------------------------------#

MAKEFLAGS	+=	--no-print-directory

# run -------------------------------------------------------------------------#

RUNARGS		:=	4 100 100 100

#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all: 
	@$(MAKE) -j makeall

clean:
	@rm -rf $(DIR_BUILD)

fclean:
	@rm -rf $(DIR_BUILD)
	@rm -f	$(NAME) \
			$(NAME_DEBUG) \
			$(NAME_SAN)

re: fclean
	@$(MAKE) -j makeall

run: all
	- ./$(NAME) $(RUNARGS)


debug:
	@$(MAKE) -j makedebug

valgrind: debug
	- valgrind $(VAL_FLAGS) $(VAL_FLAGS_C) ./$(NAME_DEBUG) $(RUNARGS)

valgrind_p: debug
	- valgrind $(VAL_FLAGS) ./$(NAME_DEBUG) $(RUNARGS)

sanitize:
	@$(MAKE) -j makesanitize
	- ./$(NAME_SAN) $(RUNARGS)

sanitizebonus:
	@$(MAKE) -j makesanitizeb
	- ./$(NAME_SANB) $(RUNARGS)

makeall:		$(NAME)
makebonus:		$(NAME_BONUS)
makedebug:		$(NAME_DEBUG)
makedebugb:		$(NAME_DEBUGB)
makesanitize:	$(NAME_SAN)
makesanitizeb:	$(NAME_SANB)

$(NAME): $(OBJ)
	@$(CC) $(CC_FLAGS) $(OBJ) $(L_FLAG) $(l_FLAG) -o $(NAME)
	$(info created : $(NAME))

$(NAME_DEBUG): $(OBJ_DEBUG)
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUG) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUG)
	$(info created : $(NAME_DEBUG))

$(NAME_SAN): $(OBJ_SAN)
	@$(CC) $(OBJ_SAN) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SAN)
	$(info created : $(NAME_SAN))

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/debug/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -g -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/sanitize/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(SAN_FLAGS) -c $< -o $@
	$(info created : $@)

-include $(DEPS)

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all \
		clean \
		fclean \
		re \
		run \
		debug \
		valgrind \
		valgrind_p \
		sanitize \
		makeall \
		makedebug \
		makesanitize