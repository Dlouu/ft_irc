MAKEFLAGS += --silent
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g3
SRCS =	main.cpp\
		
OBJ = $(addprefix $(BIN_DIR)/,$(SRCS:.cpp=.o))
NAME = server
SRCS_DIR = .
BIN_DIR = ./bin

# ------------------------------ Colors ------------------------------

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m

# ------------------------------ Messages ------------------------------

COMP_START	=	echo "\n🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Starting the compilation...\n"
COMP_END	=	echo "\n🏗️  $(BOLD_YELLOW)Make: $(NO_COLOR)Compilation done\n"
CLEANED		=	echo "\n💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files \n"
FCLEANED	=	echo "\n🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed the executables \n"

all : $(NAME)

$(NAME) : $(OBJ)
	@$(COMP_START)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@$(COMP_END)

$(BIN_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -rf $(BIN_DIR)
	@$(CLEANED)

fclean : clean
	rm -f $(NAME)
	@$(FCLEANED)

re : fclean all

.PHONY : all clean fclean re