#include <stdlib.h>
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
