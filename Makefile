NAME     = webserv
GCC      = c++
CFLAGS   = -Wall -Wextra -Werror -std=c++98 -I./include -fsanitize=address
RM       = rm -rf
OUTPUT   = ./$(NAME)
LIBS     = -I./include/

# Compiled directories
SRC = src
OBJ = obj
SUBDIRS = main parseConfig

# Folder directions
SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

# File directions
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(LIB_DIR) Makefile $(OBJS)
	@$(GCC) -o $(NAME) $(OBJS) -g $(CFLAGS) -lncurses

$(OBJ)/%.o: $(SRC)/%.cpp $(LIB_DIR)
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@$(GCC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all