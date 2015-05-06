##
## Makefile for monlongserpent in /home/buchse_a/Projects/
##
## Made by Antoine Buchser
## Login   <buchse_a@epitech.net>
##
## Started on  Fri Feb  6 11:34:26 2015 Antoine Buchser
## Last update Mon Apr 20 15:18:23 2015 Thomas MORITZ
##

CXX		  =  g++

NAME		  =  bomberman

RM		  =  rm -f
MKDIR		  =  mkdir -p

SRCS_DIR	  =  src
SRCS		  =  main.cpp \
		     App.cpp \
		     Config.cpp \
		     \
		     Menu.cpp \
		     Level.cpp \
		     Character.cpp \
		     Map.cpp \
		     Position.cpp \
		     \
		     Graphics/Map.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  Exception.hpp \
		     App.hpp \
		     Config.hpp \
		     Observer.hpp \
		     \
		     Menu.hpp \
		     Level.hpp \
		     Character.hpp \
		     Map.hpp \
		     Position.hpp \
		     Graphics.hpp

LGDL_DIR	  =  libgdl

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CXXFLAGS	  += -I./inc
CXXFLAGS	  += -lpthread
CXXFLAGS	  += -I$(LGDL_DIR)/includes -L$(LGDL_DIR)/libs -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2
CXXFLAGS	  += -std=c++11 -Wall -Wextra -W -Werror -fPIC

CXXFLAGS	  += -g


#######################
## COMPILATION RULES ##
#######################

$(NAME):		$(OBJS)
			$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)
			export LD_LIBRARY_PATH=$(LGDL_DIR)/libs

all:			$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.cpp $(DEPS)
				@$(MKDIR) $(OBJS_DIR)/Graphics
		        @$(MKDIR) $(OBJS_DIR)
			$(CXX) $(CXXFLAGS) -c -o $@ $<

################
## MISC RULES ##
################

clean:
		     $(RM) -r $(OBJS_DIR)

fclean:		     clean
		     $(RM) $(NAME)

re:		     fclean all

.PHONY: re fclean clean all
