# Compiler binaries and options
CC=g++
RM=rm -f
RMDIR=rm -rf
CPPFLAGS=-g -Wall -std=c++17
LDFLAGS=-g

# Source files
SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src/,,$(SRCS:.cpp=.o))

# Compiled binary filename
BINOUT=project
DATADIR=data

# Main compilation target
all: project

project: $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINOUT) $(OBJS)

# Compile .cpp files to .o files
%.o: src/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# Remove all object files
clean:
	$(RM) $(OBJS)
	$(RM) .depend

# Remove all object and temporary files
distclean: clean
	$(RM) *~ .depend

# Remove all data files
rmdata:
	$(RMDIR) data

# Remove everything
cleanall: distclean rmdata

# Run binary, create required data directory if missing
run:
	if [ ! -d "$(DATADIR)" ]; then mkdir "$(DATADIR)"; fi
	./$(BINOUT)