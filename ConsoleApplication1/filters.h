#pragma once


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


struct bmp_image* greyscale(const struct bmp_image* image);

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep);