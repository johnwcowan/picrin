CC=gcc
CFLAGS=-Wall -Wextra -std=c99

ifeq ($(findstring CYGWIN,$(shell uname -s)), CYGWIN)
  XFILE_LIB=cygxfile.dll
  PICRIN_LIB=cygpicrin.dll
else
  XFILE_LIB=libxfile.so
  PICRIN_LIB=libpicrin.so
endif

all: deps release

deps:
	git submodule update --init
	$(CC) $(CFLAGS) -shared -fPIC extlib/xfile/*.c -o lib/$(XFILE_LIB) -I./extlib/xfile

release: CFLAGS += -DDEBUG=0 -O3
release: build

debug: CFLAGS += -g -DDEBUG=1 -O0
debug: build

build: build-lib build-main

build-main:
	$(CC) $(CFLAGS) tools/main.c src/*.c -o bin/picrin -I./include -I./extlib -L./lib -lreadline -lm -lxfile

build-lib:
	cd src; \
	  yacc -d parse.y; \
	  flex scan.l
	$(CC) $(CFLAGS) -shared -fPIC src/*.c -o lib/$(PICRIN_LIB) -I./include -I./extlib -L./lib -lm -lxfile

clean:
	rm -f src/y.tab.c src/y.tab.h src/lex.yy.c
	rm -f lib/$(PICRIN_LIB)
	rm -f bin/picrin

run:
	bin/picrin

tak: release
	bin/picrin etc/tak.scm

lines: clean
	wc -l `find . -name "*.[chyl]"`

no-act:
	bin/picrin -e '' > /dev/null
