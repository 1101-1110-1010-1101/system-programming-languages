#include <stdlib.h>
#include <stdio.h>
#include "bmp_tools.h"

bmp_header* read_bmp_header(FILE* file) {
  bmp_header* header = (bmp_header*)malloc(sizeof(bmp_header));
  fread(header, sizeof(bmp_header), 1, file);
  return header;
}

void read_bmp_data(FILE* file, image* img) {
  /* load raw (padded) data from source image */
  bmp_header* header = read_bmp_header(file);
  uint8_t* raw = (uint8_t*)malloc(header->img_size);
  fseek(file, header->img_data_offset, SEEK_SET);
  fread(raw, header->img_size, 1, file);

  /* now its time to remove some padding folks */
  uint32_t pad = header->width % 4;    // this is padding - how many bytes we should add for each line
  if (pad == 0) {
    img->data = (pixel*) raw;
  }
  else {
    pixel* valid_data = (pixel*)malloc(header->width * header->height * sizeof(pixel));
    uint64_t acc_pad;                   // padding accumulator
    uint64_t cur_pixel;
    uint32_t h, w;
    for (h = 0; h < header->height; h++) {
      acc_pad = h * pad;
      for (w = 0; w < header->width; w++) {
        cur_pixel = h * header->width + w;
        valid_data[cur_pixel] = *(pixel*) (raw + cur_pixel * sizeof(pixel) + acc_pad);
      }
    }
    free(raw);
    img->data = valid_data;
  }
  img->width = header->width;
  img->height = header->height;
}

bmp_header* create_bmp_header(image* img) {
  bmp_header* header = (bmp_header*)malloc(sizeof(bmp_header));

  header->file_type[0] = 'B';
  header->file_type[1] = 'M';
  header->reserved_zero = 0;
  header->img_data_offset = sizeof(bmp_header);
  header->header_size = header->img_data_offset - 14;
  header->width = img->width;
  header->height = img->height;
  header->planes = 1;
  header->bits_per_pixel = 24;
  header->compression = 0;
  header->img_size = img->height * img->width * sizeof(pixel) 
    + img->height * (img->width % 4);
  header->pix_per_meter_hor = 2835;
  header->pix_per_meter_ver = 2835;
  header->number_of_colors = 0;
  header->number_of_important_colors = 0;
  header->file_size = header->img_data_offset + header->img_size;

  return header;
}
