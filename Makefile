# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/21 16:16:13 by irhett            #+#    #+#              #
#    Updated: 2017/09/22 19:37:04 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ssl

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra #-g -fsanitize=address
FLAGS		=	$(CFLAGS) $(XFLAGS)

SRC_DIR		=	src
SRC_FILE	=	main.c interpret.c init_commands.c commands.c call_command.c \
				base64_p.c base64_e.c base64_u.c base64_tools.c \
				desecb_p.c desecb_e.c desecb_u.c \
				descbc_p.c descbc_e.c descbc_u.c \
				command_error.c input_output.c \
				des_block_perm.c des_validate.c des_zipper.c \
				des_sbox.c des_round.c des_key_perm.c des_parse.c \
				hex.c swap.c raw.c \
				test_des_print_key.c \
				#3des_p.c 3des_e.c 3des_u.c \


SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILE))

OBJ_DIR		=	obj
OBJ_FILE	=	$(SRC_FILE:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE))

LIBFT_DIR	=	libft
LIBFT_LIB	=	libft.a
LIBFT_INC	=	inc
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

INC_DIR		=	-I $(LIBFT_DIR)/$(LIBFT_INC) -I inc

.PHONY: libft all clean fclean re

all: $(LIBFT) $(NAME)

$(NAME): $(SRCS) | $(OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) $(INC_DIR) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -c $^ $(CFLAGS) $(INC_DIR) -o $@

clean:
	@echo "cleaning libft"
	@cd $(LIBFT_DIR) && make clean
	@echo "removing objects"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@cd $(LIBFT_DIR) && make fclean
	@echo "removing executable"
	@rm -f $(NAME)

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
