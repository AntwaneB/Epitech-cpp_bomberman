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
		     App.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o) $(MOC_SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  Exception.hpp \
		     App.hpp

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CXXFLAGS	  += -I./inc
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
