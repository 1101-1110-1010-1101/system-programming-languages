#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "img.h"
 
int main() {
    bmp_header header;
    FILE *f = fopen("elfen_lied.bmp", "rb");
    fread(&header, 1, sizeof(header), f);
    
    pixel* data = (pixel*) malloc(header.biSizeImage);
    fseek(f, header.bOffBits, SEEK_SET);
    fread(data, 1, header.biSize, f);
    
    image img = {header.biWidth, header.biHeight, data};

    image* new_img = rotate(&img);
    save_image(new_img, "abc", header); 

    fclose(f);

    return 0;
}
