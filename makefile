CC = g++
CFLAGS = -Wall
OBJFILES = treap.o ThreadedBST.o AVL_Tree.o main.o
TARGET = dslab_assignment3

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
