#include <stdlib.h>
#include <stdio.h>
#include "img.h"

bmp_header* read_bmp_header(FILE* file) {
  bmp_header* header = (bmp_header*)malloc(sizeof(bmp_header));
  fread(header, sizeof(bmp_header), 1, file);
  return header;
}
