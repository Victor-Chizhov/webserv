NAME     = webserv
GCC      = c++
CXXFLAGS   = -Wall -Wextra -Werror -std=c++98 -I./include -g
RM       = rm -rf
OUTPUT   = ./$(NAME)
LIBS     = -I./include/

SRC = src
OBJ = obj

SRCS = $(wildcard $(SRC)/**/*.cpp)
SRCS += $(wildcard $(SRC)/*.cpp)
OBJS = $(SRCS:$(SRC)%.cpp=$(OBJ)%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB_DIR) Makefile $(OBJS)
	@$(GCC) -o $(NAME) $(OBJS) -g $(CXXFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	@$(GCC) $(CXXFLAGS) -c $< -o $@

$(OBJ):
	@mkdir -p $(OBJ)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
