#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "img.h"
 
int main() {
  FILE* input = fopen("elfen_lied.bmp", "rb");
  bmp_header* header = read_bmp_header(input);
    //image* input = (image*)malloc(sizeof(image));
    //load_image("elfen_lied.bmp", input);

    //image* new_img = rotate(input);
    //save_image(*new_img, "abc.bmp"); 

    return 0;
}
