#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "img.h"
 
int main() {
    image* input = (image*)malloc(sizeof(image));
    load_image("elfen_lied.bmp", input);

    image* new_img = input;//rotate(input);
    save_image(new_img, "abc.bmp"); 

    return 0;
}
