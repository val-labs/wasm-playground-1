EMCC=docker exec -it -w `pwd` EMS emcc -Os
call: clean all
all: index.html app.js
	node app.js
	ls -la
	bottle.py ws
app.js: hw.c Makefile
	$(EMCC) $< -o $@ -s NODERAWFS=1 -DNODERAWFS=1
index.html: hw.c Makefile
	$(EMCC) $< -o $@ --preload-file tests/hello_world_file.txt
clean:
	sh clean.sh; ls -la
