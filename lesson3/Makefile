CC=docker run -v`pwd`":/src" --rm trzeci/emscripten emcc
CFLAGS=-Os -s EXPORTED_FUNCTIONS='["_main","_eleven","_wopn","_wmsg","_wcls"]'\
 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
LDFLAGS=$(CFLAGS)
all: test
test: install index.html main.js ; node main.js
main.a: main.o eleven.o wsox.o

install: node_modules/ws
node_modules/ws: ; npm install ws
index.html: main.html ; rm -f $@ ; ln $< $@

%.a: ; rm -f $@ ; $(AR) r $@ $^
%.html: %.a ; $(CC) $(LDFLAGS) $^ -o $@
%.js:   %.a ; $(CC) $(LDFLAGS) $^ -o $@
*.o: *.h Makefile
ws:; python -mbottle ws
clean:;rm -fr *.{o,a,bc,js,html,wasm,pyc} *~ main package* node_modules
