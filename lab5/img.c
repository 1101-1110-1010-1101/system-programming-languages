#include <stdlib.h>
#include <stdio.h>
#include "img.h"

image* rotate(image* img) {
  image* rotated = (image*)malloc(sizeof(image));
  rotated->data = (pixel*)malloc(img->height*img->width*sizeof(pixel));
  rotated->width = img->height;
  rotated->height = img->width;

  uint32_t i, j;
  for (i = 0; i < img->height; ++i) {
    for (j = 0; j < img->width; ++j) {
      rotated->data[j*img->height + i] = img->data[i*img->width + j];
    }
  }
  return rotated;
}

void save_image(image* img_data, const char* filename, bmp_header header) {
  FILE* new_f = fopen(filename, "wb");                                                                                                         
  int padding = header.biWidth % 4;                                                
  uint32_t i, j;                                                              
  image* img = (image*)malloc(sizeof(image));                       
  img->width = img_data->width + padding;                            
  img->height = img_data->height;                                    
  img->data = (pixel*)calloc(1, img->height * img->width * sizeof(pixel));
                                                                                
  for (i = 0; i < img->height; ++i) {                               
	  for (j = 0; j < img->width; ++j) {
		  img->data[i * img->width + j] = img_data->data[i * img_data->width + j];
	  }                                                                         
  }                                                                           
                                                                                
  bmp_header new_header = header;                                             
  new_header.biWidth = img->width - padding;                        
  new_header.biHeight = img->height;                                
                                                                                
  fwrite(&new_header, 1, sizeof(bmp_header), new_f);                          
  fwrite(&img->data, 1, img->height * img->width * sizeof(pixel), new_f);
                                                                                                                                                 
  fclose(new_f);
} 
