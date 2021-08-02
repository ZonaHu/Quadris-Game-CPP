# The Makefile needs to create an executable called "quadris"

# Build Macro Definition

CXX = g++    #compiler
CXXFLAGS = -std=c++14 -g -Wall -MMD `pkg-config gtkmm-3.0 --cflags --libs` `pkg-config glibmm-2.4 --libs`  #compiler flags, compile using c++14
OBJECTS = GenericLevel.o Subject.o Observer.o GenericBlock.o BoardModel.o TextDisplay.o GraphicalDisplay.o Controller.o GameManager.o IBlock.o JBlock.o LBlock.o OBlock.o SBlock.o ZBlock.o TBlock.o StarBlock.o Level0.o Level1.o Level2.o Level3.o Level4.o main.o #object files
DEPENDS = ${OBJECTS:.o=.d}    #substitutes ".o" with ".d"
EXEC = quadris    #executable name

# Link step
${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}
	
# once -MMD added to the compiler flag, no more manual dependencies

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
	
-include ${DEPENDS}
