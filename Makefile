# The Makefile needs to create an executable called "quadris"

# Build Macro Definition

CXX = g++    #compiler
CXXFLAGS = -std=c++14 -g -Wall -MMD    #compiler flags, compile using c++14
OBJECTS = GenericLevel.o Subject.o Observer.o GenericBlock.o BoardModel.o TextDisplay.o GraphicalDisplay.o Controller.o GameManager.o IBlock.o main.o#object files  // TODO: to be updated
DEPENDS = ${OBJECTS:.o=.d}    #substitutes ".o" with ".d"
EXEC = quadris    #executable name

# Link step
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
	
# once -MMD added to the compiler flag, no more manual dependencies

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
	
-include ${DEPENDS}
