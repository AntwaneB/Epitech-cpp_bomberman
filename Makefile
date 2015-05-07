##
## Makefile for onfaittoutpéter in /home/buchse_a/Projects/
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
		     Menu.cpp \
		     Level.cpp \
		     Character.cpp \
		     Map.cpp \
		     Position.cpp \
		     Item.cpp \
		     Bomb.cpp \
		     \
		     Graphics/Display.cpp \
		     Graphics/Map.cpp \
		     \
		     misc/pugixml.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  Exception.hpp \
		     App.hpp \
		     Config.hpp \
		     Observer.hpp \
		     Menu.hpp \
		     Level.hpp \
		     Character.hpp \
		     IA.hpp \
		     Map.hpp \
		     Position.hpp \
		     Item.hh \
		     Bomb.hh \
		     \
		     Graphics/Display.hh \
		     Graphics/Map.hh \
		     \
		     misc/pugiconfig.hpp \
		     misc/pugixml.hpp

LGDL_DIR	  =  LibBomberman_linux_x64

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CXXFLAGS	  += -I$(INCS_DIR) -I$(INCS_DIR)/misc
CXXFLAGS	  += -lgdl_gl -lGLEW -lGL -lSDL2 -ldl -lrt -lfbxsdk -lpthread
CXXFLAGS	  += -lpthread
CXXFLAGS	  += -I$(LGDL_DIR)/includes -L$(LGDL_DIR)/libs
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
		        @$(MKDIR) $(OBJS_DIR)
			@$(MKDIR) $(OBJS_DIR)/Graphics
			@$(MKDIR) $(OBJS_DIR)/misc
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
