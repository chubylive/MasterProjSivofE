CC=g++          # define the compiler to use
TARGET=main     # define the name of the executable
SOURCES=main.cpp PrimeSieveApi.cpp
CFLAGS=-O3
LFLAGS=-lm

# define list of objects
OBJSC=$(SOURCES:.c=.o)
OBJS=$(OBJSC:.cpp=.o)

# the target is obtained linking all .o files
all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

purge: clean
	rm -f $(TARGET)

clean:
	rm -f *.o
	rm -f main
