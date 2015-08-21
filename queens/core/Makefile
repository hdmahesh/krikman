OBJDIR=./objs
GCC=g++
OFLAGS=
CFLAGS=-c -Wall -pedantic -Werror -std=c++0x
DBGFLAGS=-g -D__DEBUG__
SOURCES=State.cc \
	Value.cc \
	HillClimbBasic.cc \
	HillClimb.cc \
	util.cc \

OBJECTS=$(SOURCES:.cc=.o)
OBJECTSD=$(SOURCES:.cc=.od)

all: $(SOURCES) $(OBJECTS)

debug: $(SOURCES) $(OBJECTSD)

clean:
	rm -rf $(OBJDIR)

%.od:%.cc
	mkdir -p $(OBJDIR)
	$(GCC) $(DBGFLAGS) $(CFLAGS) $< -o $(OBJDIR)/$@

%.o:%.cc
	mkdir -p $(OBJDIR)
	$(GCC) $(OFLAGS) $(CFLAGS) $< -o $(OBJDIR)/$@

