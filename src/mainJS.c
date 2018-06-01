#include <emscripten/emscripten.h>

void EMSCRIPTEN_KEEPALIVE mainJS(){
  const char *a[6];
  a[0] = "mc";
  a[1] = "ex.m";
  a[2] = "-r";
  a[3] = "ex.r";
  a[4] = "-o";
  a[5] = "ex.c";
  main(6, a);
}
