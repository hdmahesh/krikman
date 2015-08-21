empty:=
slash:=/objs/*.o $(empty)
slashd:=/objs/*.od $(empty)
space:= $(empty) $(empty)
DIRS=../../core src $(empty)

EXENAME=ksp
EXENAMED=ksp-debug
EXEDIR=./bin
GCC=g++ -std=c++0x
LFLAGS= -Wall -pedantic -Werror
OFLAGS=
DBGFLAGS=-g -D__DEBUG__
SOURCES=main.cc
OBJECTS=$(SOURCES:.cc=.o)
OBJECTSD=$(SOURCES:.cc=.od)
SUBOBJECTS=$(subst $(space),$(slash),$(DIRS))
SUBOBJECTSD=$(subst $(space),$(slashd),$(DIRS))

all: allsub $(SOURCES) $(OBJECTS)

allsub:
	for d in $(DIRS); \
	do \
	cd $$d; \
	make all; \
	cd -; \
	done;
	mkdir -p $(EXEDIR)

debug: debugsub $(SOURCES) $(OBJECTSD)

debugsub:
	for d in $(DIRS); \
	do \
	cd $$d; \
	make debug; \
	cd -; \
	done;
	mkdir -p $(EXEDIR)

clean:
	for i in $(DIRS) ; \
	do \
	cd $$i; \
	make clean; \
	cd -; \
	done; 
	rm -rf $(EXEDIR)

%.od:%.cc
	$(GCC) $(DBGFLAGS) $(LFLAGS) $< $(SUBOBJECTSD) -o $(EXEDIR)/$(EXENAMED)

%.o:%.cc
	$(GCC) $(OFLAGS) $(LFLAGS) $< $(SUBOBJECTS) -o $(EXEDIR)/$(EXENAME)

