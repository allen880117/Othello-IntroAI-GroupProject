CC      = clang++
CFLAGS  = -Wall -std=c++11 -g
INCLUDE = -Iinclude

SRCDIR = src
SRC := $(shell find $(SRCDIR) -name '*.cpp')

EXEC = Othello.exec

# Substitution reference
OBJS = $(SRC)
DEPS := $(OBJS:%.cpp=%.d)
OBJS := $(OBJS:%.cpp=%.o)

all: $(EXEC)

# Static pattern rule
%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) $(INCLUDE) -c -MMD $<

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(INCLUDE)

clean:
	$(RM) $(DEPS) $(OBJS) $(EXEC)

-include $(DEPS)
