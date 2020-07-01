CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g -fsanitize=address
LDFLAGS =  -fsanitize=address
LBLIBS = -levent

SRC = main.cpp access/AccessClient.cpp access/ClientAccessInfo.cpp \
		service/ChatroomServiceImpl.cpp dao/OnlineUserInfoDaoImpl.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = server

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	find . -name "*.o"  | xargs rm -f