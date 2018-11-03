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
    
    FILE* new_f = fopen("res.bmp", "wb");
    int padding = img.width % 4;
    uint32_t i, j;
    image* new_new_image = (image*)malloc(sizeof(image));
    new_new_image->width = new_img->width + padding;
    new_new_image->height = new_img->height;
    new_new_image->data = (pixel*)calloc(1, new_new_image->height * new_new_image->width * sizeof(pixel));

    for (i = 0; i < new_new_image->height; ++i) {
      for (j = 0; j < new_new_image->width; ++j) {
        new_new_image->data[i * new_new_image->width + j] = new_img->data[i * new_img->width + j];
      }
    }

    bmp_header new_header = header;
    new_header.biWidth = new_new_image->width - padding;
    new_header.biHeight = new_new_image->height;   

    fwrite(&new_header, 1, sizeof(bmp_header), new_f);
    fwrite(&new_new_image->data, 1, new_new_image->height * new_new_image->width * sizeof(pixel), new_f);

    fclose(f);
    fclose(new_f);
    return 0;
}
