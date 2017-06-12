# the compiler to use
CC      = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS = -g -Wall
RM      = rm -rf

SRC_IO = io/random.c \
	io/io.c

SRC_G = graph/graph_list.c \
	graph/graph_func.c \
	graph/graph_sp.c

SRC_L = list/list.c

SRC_Q = queue/queue.c 

SRC = $(SRC_IO) $(SRC_L) $(SRC_Q) $(SRC_G)


OBJ_IO = $(SRC_IO:.c=.o)

OBJ_L = $(SRC_L:.c=.o)

OBJ_Q = $(SRC_Q:.c=.o)

OBJ_G = $(SRC_G:.c=.o)

OBJ = $(SRC:.c=.o)

default: all

all: $(OBJ)
	$(CC) $(CCFLAGS) $(SRC) -o graphLib main.c
	@echo "Build complete"

clean:
	$(RM) *.dSYM graph/*.o io/*.o list/*.o queue/*.o *.o graphLib
	@echo "Clean complete"