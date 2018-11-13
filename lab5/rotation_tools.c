#include <stdio.h>
#include <stdlib.h>
#include "bmp_tools.h"

image* rotate_image(image* img) {
  pixel* rotated = (pixel*)malloc(img->height * img->width * sizeof(pixel));
  
  uint64_t h, w;
  for (h = 0; h < img->height; h++) {
    for (w = 0; w < img->width; w++) {
      rotated[((img->width - 1 - w) * img->height) + h] = 
        img->data[(h * img->width) + w];
    }
  }
  image* res = (image*) malloc(sizeof(image));
  res->width = img->height;
  res->height = img->width;
  res->data = rotated;
  return res;
}
