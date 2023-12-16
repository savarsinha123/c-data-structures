CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = test_list
INCLUDE = -I./include   # Include path for header files

SRCDIR = src
OBJDIR = bin
SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJFILES)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o

# Create the obj directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))