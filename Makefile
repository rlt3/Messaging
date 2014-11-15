CC         := clang++

#LIBRARIES  :=-I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks
#FRAMEWORKS :=-framework Cocoa -framework SDL2

SRCDIR     := src
SOURCES    := src/main.cpp 

OBJDIR     := obj
OBJECTS    := ${SOURCES:${SRCDIR}/%.cpp=${OBJDIR}/%.o}

EXECUTABLE := slow

all: ${SOURCES} ${EXECUTABLE}

${OBJECTS}: ${OBJDIR}/%.o : ${SRCDIR}/%.cpp
	$(CC) -c $< -o $@ ${LIBRARIES}

${EXECUTABLE}: ${OBJECTS}
	${CC} -Wall -o $@ ${OBJECTS} ${LIBRARIES} ${FRAMEWORKS}

clean:
	rm -f ${OBJDIR}/*.o ${EXECUTABLE}
