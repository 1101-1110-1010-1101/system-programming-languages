#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "rotation_tools.h"
#include "bmp_tools.h"

#define exit_with_err(...) do { fprintf(stderr, __VA_ARGS__); return 1; } while (0);
 
int main(int argc, char** argv) {
  if (argc != 3)
    exit_with_err("usage: lab5 src_file.bmp dest_file.bmp\n");

  char* input_name = argv[1];
  char* output_name = argv[2];

  FILE* input = fopen(input_name, "rb");
  if (input == NULL)
    exit_with_err("Cannot open %s\n", input_name);
  FILE* output = fopen(output_name, "wb");
  if (output == NULL)
    exit_with_err("Cannot open %s for writing\n", output_name);
  image* img = (image*) malloc(sizeof(image));
  read_status r_st = read_bmp_data(input, img);

  switch (r_st) {
    case READ_ERR_SIGNATURE:
      exit_with_err("%s is not a valid bmp file\n", input_name);
    case READ_ERR_BITS_PER_PIXEL:
      exit_with_err("Only 24-bit images supported\n");
    case READ_ERR:
      exit_with_err("Error ocured while opening %s\n", input_name);
    case READ_OK:
      break;
  }

  image* rot = rotate_image(img);
  write_status w_st = write_bmp(rot, output);

  switch (w_st) {
    case WRITE_ERR:
      exit_with_err("Error ocured while saving image\n");
    case WRITE_OK:
      break;
  }

  fclose(input);
  fclose(output);

  return 0;
}
