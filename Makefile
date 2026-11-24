CXX				= c++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++20 -g

# LDFLAGS			= -lSDL2 -lGL
HEADERS			= ./includes/
SRC_DIR			= ./srcs/
OBJ_DIR			= ./objs/

CXXFLAGS += -I$(HEADERS)

SRCS			= main.cpp	\
					key.cpp	\
					utils.cpp	\
					class/Parser.cpp	\
					class/Game.cpp	\
					class/Board.cpp	\
					class/Snake.cpp \
					class/Agent.cpp	\
					class/Interpreter.cpp

OBJS			= $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))
DEPS			= $(OBJS:.o=.d)

NAME			= Learn2Slither

all: $(NAME)

$(NAME): $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
# $(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
		@mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re