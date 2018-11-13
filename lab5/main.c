#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rotation_tools.h"
#include "bmp_tools.h"
 
int main() {
  FILE* input = fopen("elfen_lied.bmp", "rb");
  FILE* output = fopen("result.bmp", "wb");
  image* img = (image*) malloc(sizeof(image));
  read_bmp_data(input, img);
  image* rot = rotate_image(img);
  write_bmp(rot, output);
  fclose(input);
  fclose(output);

  return 0;
}
