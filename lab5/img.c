#include <stdlib.h>
#include <stdio.h>
#include "img.h"

image* rotate(image* img) {
  image* rotated = (image*)malloc(sizeof(image));
  rotated->data = (pixel*)malloc(img->height*img->width*sizeof(pixel));
  rotated->width = img->height;
  rotated->height = img->width;

  uint32_t i, j;
  for (i = 0; i < img->height; i++) {
    for (j = 0; j < img->width; j++) {
      rotated->data[((img->width - 1 - j) * img->height) + i] = img->data[(i*img->width) + j];
    }
  }
  return rotated;
}

void save_image(image* img, const char* filename) {
  FILE* new_f = fopen(filename, "wb+");                                                                                                         
  int padding = img->width % 4;                                                
  uint32_t i, j;                                                              

  uint64_t size_of_data = img->width * img->height * sizeof(pixel) + img->height * padding;
  uint8_t* data = (uint8_t*)calloc(1, size_of_data);
  for (uint64_t i = 0; i < img->height; i++) {
    uint64_t pad = i * padding;
    for (uint64_t j = 0; j < img->width; j++) {
      uint64_t k = i * img->width + j;
      *((pixel*)(data + sizeof(pixel) * k + pad)) = img->data[k];
    }
  }

  bmp_header* header = (bmp_header*)malloc(sizeof(bmp_header));
  header->bfType = 19778;
  header->bfileSize = size_of_data + sizeof(bmp_header);
  header->bfReserved = 0;
  header->bOffBits = sizeof(bmp_header);
  header->biSize = 40;
  header->biPlanes = 1;
  header->biBitCount = 24;
  header->biCompression = 0;
  header->biSizeImage = size_of_data;
  header->biXPelsPerMeter = 2835;
  header->biYPelsPerMeter = 2835;
  header->biClrUsed = 0;
  header->biClrImportant = 0;
  header->biWidth = img->width;
  header->biHeight = img->height;                                  

  fwrite(header, 1, sizeof(bmp_header), new_f);   
  fwrite(img->data, 1, size_of_data, new_f);
  fclose(new_f);
} 

void load_image(const char* filename, image* img) {
  FILE* f = fopen(filename, "rb");
  bmp_header header;
  fread(&header, 1, sizeof(header), f);
  uint8_t* data = (uint8_t*)malloc(header.biSizeImage);
  fseek(f, header.bOffBits, SEEK_SET);
  fread(data, 1, header.biSizeImage, f);
  img->data = (pixel*)malloc(header.biHeight * header.biWidth * sizeof(pixel));

  int padding = header.biWidth % 4;
  uint32_t i, j;
  for(i = 0; i < header.biHeight; ++i) {
    for(j = 0; j < header.biWidth; ++j) {
      img->data[i * header.biWidth + j] = *(pixel*)(((uint8_t*)data) + sizeof(pixel) * (i * header.biWidth + j) + padding * i);
    }
  }
  img->height = header.biHeight;
  img->width = header.biWidth;
  fclose(f);
}
