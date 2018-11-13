#ifndef BMP
#define BMP

#include <stdint.h>
typedef struct __attribute__((packed)){
  char file_type[2];
  uint32_t file_size;
  uint32_t reserved_zero;
  uint32_t img_data_offset;
  uint32_t header_size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bits_per_pixel;
  uint32_t compression;
  uint32_t img_size;
  uint32_t pix_per_meter_hor;
  uint32_t pix_per_meter_ver;
  uint32_t number_of_colors;
  uint32_t number_of_important_colors;
} bmp_header;                                                                   
                                                                                
typedef struct {                                                                
  uint8_t b, g, r;                                                            
} pixel;

typedef struct {
  uint64_t width, height;
  pixel* data;
} image;

bmp_header* read_bmp_header(FILE* file);
void read_bmp_data(FILE* file, image* img);
bmp_header* create_bmp_header(image* img);
#endif
