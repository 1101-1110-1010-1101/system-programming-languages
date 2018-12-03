#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp_tools.h"
#include "sepia.h"

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#define exit_with_err(...) do { fprintf(stderr, __VA_ARGS__); return 1; } while (0);
void image_sepia_sse(pixel_t* pixel, uint32_t size);
 
#define BENCHMARK_NUM_RUNS 250UL




void sepia_sse_inplace(image_t *img) {
    if (img->height * img->width < 4){
        for (int i = 0; i < img->height * img->width; ++i){
            sepia_one(img->data + i);
        }
        return;
    }
    image_sepia_sse(img->data, img->height * img->width - (img->height * img->width) % 4);
    for (int i  = img->height * img->width - (img->height * img->width) % 4; i < img->height * img->width; ++i){
        sepia_one(img->data + i);
    }
}


void calculate_time(image_t* img) {
  struct rusage r;
  struct timeval start, end;

  getrusage(RUSAGE_SELF, &r); start = r.ru_utime;

  for (uint64_t i = 0; i < BENCHMARK_NUM_RUNS; i++) { sepia_sse_inplace(img); }

  getrusage(RUSAGE_SELF, &r); end = r.ru_utime;

  long res = ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;

  printf("SSE: %ld μs (average for %lu runs)\n", res / BENCHMARK_NUM_RUNS, BENCHMARK_NUM_RUNS);

  // ---

  getrusage(RUSAGE_SELF, &r); start = r.ru_utime;

  for (uint64_t i = 0; i < BENCHMARK_NUM_RUNS; i++) { sepia_c_inplace(img); }

  getrusage(RUSAGE_SELF, &r); end = r.ru_utime;

  res = ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;

  printf("Native C: %ld μs (average for %lu runs)\n", res / BENCHMARK_NUM_RUNS, BENCHMARK_NUM_RUNS);
}

int main(int argc, char** argv) {
  if (argc != 2)
    exit_with_err("usage: lab7 src_file.bmp\n");

  char* input_name = argv[1];

  FILE* input = fopen(input_name, "rb");
  if (input == NULL)
    exit_with_err("Cannot open %s\n", input_name);
  FILE* output_c = fopen("out/result_c.bmp", "wb");
  FILE* output_sse = fopen("out/result_sse.bmp", "wb");
  image_t* img = (image_t*) malloc(sizeof(image_t));
  read_status r_st = read_bmp_data(input, img);

  calculate_time(img);

  switch (r_st) {
    case READ_ERR_SIGNATURE:
      exit_with_err("%s is not a valid bmp file\n", input_name);
    case READ_ERR_BITS_PER_PIXEL:
      exit_with_err("Only 24-bit images supported\n");
    case READ_ERR:
      exit_with_err("Error ocured while opening %s\n", input_name);
    case READ_OK:
      break;
  }
  
  image_t* img_c = img;
  sepia_c_inplace(img_c);
  write_bmp(img_c, output_c);

  sepia_sse_inplace(img);
  write_bmp(img, output_sse);

  fclose(input);
  fclose(output_c);
  fclose(output_sse);

  return 0;
}
