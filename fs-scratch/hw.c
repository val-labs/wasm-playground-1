#include <stdio.h>
#include <emscripten.h>

#ifdef NODERAWFS
# define CWD ""
#else
# define CWD "/working/"
#endif

int main() {
  printf("E[%s]\n", CWD);
  FILE *file = fopen("tests/hello_world_file.txt", "rb");
  if (!file) {
    printf("cannot open file\n");
    return 1;
  }
  while (!feof(file)) {
    char c = fgetc(file);
    if (c != EOF) {
      putchar(c);
    }
  }
  fclose (file);
  printf("X[%s]\n", CWD);
  return 0;
}
