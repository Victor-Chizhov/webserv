#CLIENT = client
SERVER = server

#SRCS_C =	./client.cpp ./tcpClient.cpp
SRCS_S =	./server.cpp ./tcpServer.cpp

#OBJS_C = $(SRCS_C:.cpp=.o)
OBJS_S = $(SRCS_S:.cpp=.o)
CPP = c++

all: $(SERVER)


%.o : %.cpp 
	$(CPP) -c $< -o $@

#$(CLIENT) : $(OBJS_C)
#	$(CPP) $(OBJS_C) -o $(CLIENT)

$(SERVER) : $(OBJS_S)
	$(CPP) $(OBJS_S) -o $(SERVER)


clean:
	rm -rf $(OBJS_S)

fclean:
	rm -rf $(OBJS_S) $(SERVER)

re: fclean all

.PHONY:	all clean fclean re bonus
