CC=docker run -v`pwd`":/src" --rm trzeci/emscripten emcc
CFLAGS=-Os -s EXPORTED_FUNCTIONS='["_main","_wopn","_wmsg","_wcls"]'\
 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
LDFLAGS=$(CFLAGS)
#call: clean all
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
all: clean test2.tar.gz test
test: index.html
	node test2.js
	make ws
test2.tar.gz: test2.a ./include/*
	rm -fr test2.tar.gz lib
	mkdir lib ; cp test2.a lib
	tar -cvf test2.tar.gz lib include
test2.a: $(SRCS)
	$(CC) src/*.c -c -I ./include
	rm -f $@ ; $(AR) r $@ *.o
index.html: test2.html ; rm -f $@ ; ln $< $@

%.a: ; rm -f $@ ; $(AR) r $@ $^
%.html: %.a ; $(CC) $(LDFLAGS) $^ -o $@
%.js:   %.a ; $(CC) $(LDFLAGS) $^ -o $@
*.o: *.h Makefile
ws:; python -mbottle ws
clean:;rm -fr *.{o,a,bc,js,html,wasm,pyc,gz} *~ main lib; ls -la
