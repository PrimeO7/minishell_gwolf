# text effects
RESET := \033[0m
BOLD := \033[1m
BLACK := \033[30m
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
BLUE := \033[34m

# directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LIB_DIR_FT := $(LIB_DIR)/libft
INC_DIR := inc
DEP_DIR := $(OBJ_DIR)/dep
TEST_DIR := test

# include
INC := -I $(INC_DIR) -I lib/libft/

# libraries
LIB_FT := -L $(LIB_DIR_FT) -l ft

# compiling
CC := cc
CFLAGS = -Wall -Werror -Wextra
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d
COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) $(INC) -c

# targets
NAME := minishell
LIBFT := $(LIB_DIR_FT)/libft.a

# source files
SRC :=	main.c \
		ft_memory.c \
		ft_string.c \
		replace_token.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

# prompt_replace_h.c \
		prompt_replace_small.c \
		prompt_replace_u.c \
		prompt_replace_w.c \
		prompt.c

# objects
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

# dependencies
DEPFILES :=$(SRC:%.c=$(DEP_DIR)/%.d)

# test
TEST_SRC := test_main.c \
			test_replace_token.c
TEST_SRCS := $(addprefix $(TEST_DIR)/, $(TEST_SRC))

.PHONY: all, clean, fclean, re, debug, obj, dep, test
.SILENT:

all: $(NAME)
	echo "$(GREEN)ALL DONE!$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIB_FT) -o $@
	echo "$(GREEN)$(NAME) created!$(RESET)"

debug: CFLAGS = -g
debug: $(NAME)
	echo "$(GREEN)DEBUG ready!$(RESET)"

test: CFLAGS = -g -DTESTING
test: clean $(TEST_SRCS) $(OBJS)
	$(CC) $(INC) $(CFLAGS) $(TEST_SRCS) $(OBJS) $(LIB_FT) -o tester
	echo "$(GREEN)tester created!$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_DIR)/%.d | $(DEP_DIR)
	$(COMPILE) $< -o $@

$(DEP_DIR): ; mkdir -p $@

$(DEPFILES):

$(LIBFT):
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -s -C $(LIB_DIR)/libft

clean:
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)minishell$(RESET)]\n"
	rm -rf $(OBJ_DIR)
	printf "$(RED)removed subdir $(OBJ_DIR)$(RESET)\n"

fclean: clean
	rm -rf $(NAME)
	printf "$(RED)clean bin $(NAME)$(RESET)\n"
	rm -rf tester
	printf "$(RED)clean bin tester(RESET)\n"
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) --no-print-directory -C $(LIB_DIR_FT) fclean

re: fclean all

include $(wildcard $(DEPFILES))