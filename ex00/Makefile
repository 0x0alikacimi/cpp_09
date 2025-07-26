NAME = btc

SRC_FILES = main.cpp BitcoinExchange.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

HEADERS = BitcoinExchange.hpp

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean :
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
