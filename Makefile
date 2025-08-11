MAKEFLAGS += --silent
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g3 -Iincludes
SRCS =	main.cpp \
		Server/Server.cpp \
		Server/signal.cpp\
		Command/commands/cap.cpp \
		Command/commands/invite.cpp \
		Command/commands/join.cpp \
		Command/commands/kick.cpp \
		Command/commands/mode.cpp \
		Command/commands/nick.cpp \
		Command/commands/pingpong.cpp \
		Command/commands/privmsg.cpp \
		Command/commands/topic.cpp \
		Command/commands/user.cpp \
		Command/Command.cpp \
		Client/Client.cpp
		
OBJ = $(addprefix $(BIN_DIR)/,$(SRCS:.cpp=.o))
NAME = ircserv
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

dlou: fclean
	git add .
	git commit -m "Dlou : $(m)"
	git push origin dlou

.PHONY : all clean fclean re dlou