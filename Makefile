CC = gcc
# CFLAGS = -Wall -Wextra -std=c99 -g
# CFLAGS = -std=c99
CFLAGS = 
LDFLAGS = 

# Source files and executable
SRCS = main.c # lexer.c parser.c
OBJS = $(SRCS:.c=.o)
EXEC = seesh 

# Default target: compile and link
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile .c files to .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

# Rebuild everything (useful when modifying headers or major changes)
rebuild: clean all

# Run the shell after building (if you want to automate running after compilation)
run: $(EXEC)
	./$(EXEC)

# Debug target (compile with debugging symbols)
debug: CFLAGS += -g
debug: clean all

