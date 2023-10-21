SERVER = server

SRCS_S =	./server.cpp ./tcpServer.cpp

OBJS_S = $(SRCS_S:.cpp=.o)
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(SERVER)


%.o : %.cpp 
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(SERVER) : $(OBJS_S)
	$(CPP) $(OBJS_S) -o $(SERVER)


clean:
	rm -rf $(OBJS_S)

fclean:
	rm -rf $(OBJS_S) $(SERVER)

re: fclean all

.PHONY:	all clean fclean re bonus
