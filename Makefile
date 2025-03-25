# =======================================
# Main Variables - Variables / Values
# =======================================

CC			=	cc
NAME		=	pipex
CCFLAGS 		?=	-Wall -Werror -Wextra

# =======================================
# Main Directories - Paths
# =======================================

SRCS		=	pipex.c		\
				parsing.c	\
				init.c		\

OBJS		= $(SRCS:.c=.o)

SRC_D		=	srcs/
OBJ_D		=	objs/
INC_D		=	-Iincludes \
				-Ilibs/Libft/includes
LIBS_D		=	-Ilibs/Libft


# =======================================
# Objets Files
# =======================================

.PHONY: all
all: 
	$(MAKE) -C libs/Libft
	$(MAKE) $(NAME)

OBJS	:= $(addprefix $(OBJ_D), $(OBJS))
SRCS	:= $(addprefix $(SRC_D), $(SRCS))

$(NAME):$(OBJS)
	$(CC) $(CCFLAGS) $(INC_D) $(OBJS) -lm libs/Libft/libft.a -o $@

$(OBJ_D)%.o: $(SRC_D)%.c libs/Libft/libft.a | $(OBJ_D) libs/Libft/includes includes/pipex.h
	$(CC) $(CCFLAGS) $(INC_D) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_D)
	$(MAKE) clean -C libs/Libft

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	$(MAKE) fclean -C libs/Libft

.PHONY: debug
debug:
	$(MAKE) CCFLAGS="-g3"

.PHONY: re
re:	fclean all
	$(MAKE) re -C libs/Libft

$(OBJ_D):
	mkdir -p $(OBJ_D)
