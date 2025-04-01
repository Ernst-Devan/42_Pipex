# =======================================
# Main Variables - Variables / Values
# =======================================

CC			=	cc
NAME		=	pipex
CCFLAGS 		?=	-Wall -Werror -Wextra -MMD -MP

# =======================================
# Main Directories - Paths
# =======================================

SRCS		=	pipex.c		\
				parsing.c	\
				init.c		\
				errors.c	\

OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)

SRC_D		=	srcs/
OBJ_D		=	objs/
INC_D		=	-Iincludes \
				-ILibft/includes

# =======================================
# Objets Files
# =======================================

.PHONY: all
all: 
	$(MAKE) -C Libft
	$(MAKE) $(NAME)

OBJS	:= $(addprefix $(OBJ_D), $(OBJS))
SRCS	:= $(addprefix $(SRC_D), $(SRCS))

$(NAME):$(OBJS)
	$(CC) $(CCFLAGS) $(INC_D) $(OBJS) -lm Libft/libft.a -o $@

$(OBJ_D)%.o: $(SRC_D)%.c | $(OBJ_D)
	$(CC) $(CCFLAGS) $(INC_D) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_D)
	$(MAKE) clean -C Libft

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	$(MAKE) fclean -C Libft

.PHONY: debug
debug:
	$(MAKE) CCFLAGS="-g3"

.PHONY: re
re:	fclean all

$(OBJ_D):
	mkdir -p $(OBJ_D)

-include $(DEPS)