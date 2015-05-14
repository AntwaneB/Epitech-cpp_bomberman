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
		     Clock.cpp \
		     \
		     Menu.cpp \
		     Level.cpp \
		     Character.cpp \
		     Map.cpp \
		     Position.cpp \
		     Item.cpp \
		     Bomb.cpp \
		     Block.cpp \
		     BonusItem.cpp \
		     \
		     Graphics/Display.cpp \
		     Graphics/Player.cpp \
		     Graphics/Level.cpp \
		     Graphics/Menu.cpp \
		     Graphics/Object.cpp \
		     Graphics/Cube.cpp \
		     Graphics/Map.cpp \
		     Graphics/Ground.cpp \
		     Graphics/Character.cpp \
		     Graphics/Bomb.cpp \
		     \
		     misc/pugixml.cpp \
		     \
		     IA.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  global.hh \
		     Exception.hpp \
		     App.hpp \
		     Config.hpp \
		     Clock.hpp \
		     \
		     Observer.hpp \
		     Menu.hpp \
		     Level.hpp \
		     Character.hpp \
		     IA.hpp \
		     Map.hpp \
		     Position.hpp \
		     Item.hh \
		     Bomb.hh \
		     Block.hh \
		     BonusItem.hh \
		     \
		     Graphics/Display.hh \
		     Graphics/Level.hh \
		     Graphics/Menu.hh \
		     Graphics/Object.hh \
		     Graphics/Cube.hh \
		     Graphics/Map.hh \
		     Graphics/Ground.hh \
		     Graphics/Character.hh \
		     Graphics/Bomb.hh \
		     Graphics/Player.hh \
		     \
		     misc/pugiconfig.hpp \
		     misc/pugixml.hpp \
		     \
		     IA.hpp

LGDL_DIR	  =  libgdl

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CXXFLAGS	  += -I$(INCS_DIR) -I$(INCS_DIR)/misc
CXXFLAGS	  += -I$(LGDL_DIR)/includes -L$(LGDL_DIR)/libs
CXXFLAGS	  += -lgdl_gl -lGLEW -lGL -lSDL2 -ldl -lrt -lfbxsdk -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS	  += -std=c++11 -Wall -Wextra -W -Werror -fPIC

CXXFLAGS	  += -g


#######################
## COMPILATION RULES ##
#######################

$(NAME):		$(OBJS)
			$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

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
