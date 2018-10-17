CC=docker run -v`pwd`":/src" --rm trzeci/emscripten emcc
CFLAGS=-Os
all: test
test: index.html main.js ; node main.js
main.a: main.o eleven.o
index.html: main.html ; rm -f $@ ; ln $< $@

%.a: ; rm -f $@ ; $(AR) r $@ $^
%.html: %.a ; $(CC) $(LDFLAGS) $^ -o $@
%.js:   %.a ; $(CC) $(LDFLAGS) $^ -o $@
*.o: *.h Makefile
ws:; python -mbottle ws
clean:;rm -fr *.{o,a,bc,js,html,wasm,pyc} *~ main
