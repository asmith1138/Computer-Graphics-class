##########################################################
#  CMPSC 457 Section 001                                 #
#  Homework 1                                            #
#                                                        #
#  YOUR NAME                                             #
#  YOUR ACCESS ID                                        #
#                                                        #
#  DATE OF SUBMISSION                                    #
##########################################################




##########################################################
#  COMP 597                                              #
#  Simple Makefile for HW 2                              #
#                                                        #
#  Sukmoon Chang                                         #
#  sukmoon@psu.edu                                       #
#                                                        #
#                                                        #
#                                                        #
#  Your source codes should be named as                  #
#                                                        #
#            template.cxx                                #
#                                                        #
#                                                        #
#  To compile your program, type                         #
#                                                        #
#            make template                               #
#                                                        #
#  or, simply type                                       #
#                                                        #
#            make                                        #
#                                                        #
#  on your shell.                                        #
#                                                        #
#                                                        #
#  To run your program, type                             #
#                                                        #
#            make run                                    #
#                                                        #
#                                                        #
#  To remove the executable 'template' and other backup  #
#  files (e.g., template.cxx~, etc), type                #
#                                                        #
#            make clean                                  #
#                                                        #
##########################################################


# compiler to be used
CC = g++

# flags to the compiler
CXX_FLAGS = -Wall -ansi -pedantic





# path to directories containing header files
INC_DIR = -I.

# GL related libraries
GL_LIBS = -lglut -lGLU -lGL

# X related libraries
X_LIBS = -lXext -lm






#### TARGETS ####

template: template.cxx
	$(CC) -o template template.cxx $(CXX_FLAGS) $(INC_DIR) $(GL_LIBS) $(X_LIBS)

run: template
	./template

clean:
	rm -f template  *.o *~
