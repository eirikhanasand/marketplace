# Compiler binaries and options
CC=g++
RM=rm -f
RMDIR=rm -rf
CPPFLAGS=-g -Wall -std=c++11
LDFLAGS=-g

# Source files
SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src/.cpp,.o,$(SRCS))

# Compiled binary filename
BINOUT=prosjekt
DATADIR=data

# Main compilation target
all: prosjekt

prosjekt: $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINOUT) $(OBJS)

# Compiled project dependencies
depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CC) $(CPPFLAGS) -MM $^>>./.depend;

# Remove all object files
clean:
	$(RM) $(OBJS)

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

# Dynamically generated dependency file
include .depend
