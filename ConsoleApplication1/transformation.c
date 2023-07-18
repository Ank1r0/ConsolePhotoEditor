#include "transformations.h"
#include <stdlib.h>
#include <math.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	size_t size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	for (size_t i = 0; i < image->header->height; ++i)
	{
		for (size_t j = 0; j < image->header->width; ++j)
		{
			new_image->data[i*image->header->width + j] =
				image->data[(i + 1)*image->header->width - 1 - j];
		}
	}
	return new_image;
}

struct bmp_image* flip_vertically(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	size_t size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	for (size_t i = 0, k = image->header->height - 1; i < image->header->height; ++i, --k)
	{
		for (size_t j = 0; j < image->header->width; ++j)
		{
			new_image->data[i * image->header->width + j] =
				image->data[k * image->header->width + j];
		}
	}
	return new_image;
}

struct bmp_image* rotate_left(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	size_t size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	for (size_t i = 0; i < image->header->width; ++i)
	{
		for (size_t j = 0; j < image->header->height; ++j)
		{

			new_image->data[(i + 1) * image->header->height - 1 - j] =
				image->data[j * image->header->height + i];
		}
	}
	return new_image;
}

struct bmp_image* rotate_right(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	size_t size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	for (size_t i = 0; i < image->header->width; ++i)
	{
		for (size_t j = 0; j < image->header->height; ++j)
		{
			new_image->data[j * image->header->height + i] =
				image->data[(i + 1) * image->header->height - 1 - j];
		}
	}
	return new_image;
}

struct bmp_image* crop(const struct bmp_image* image, const int start_y, const int start_x, const int height, const int width)
{
	if (start_x < 0 || start_y < 0 || start_x + width > image->header->width 
		|| start_y + height > image->header->height || image == NULL)
		return NULL;
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	size_t size = width * height;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;
	new_image->header->height = height;
	new_image->header->width = width;
	new_image->header->size = 54 + size * sizeof(struct pixel);
	size_t k = 0;
	
	int y = image->header->height - height - start_y;
	
	for (int i = y; i < y + height; ++i)
	{
		for (int j = start_x; j < start_x + width; ++j)
		{
			new_image->data[k++] = image->data[i*image->header->width + j];
		}
	}
	return new_image;
}


struct bmp_image* scale(const struct bmp_image* image, float factor)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;
	new_image->header->width = (int)round(image->header->width * factor);
	new_image->header->height = (int)round(image->header->height * factor);
	size_t size = new_image->header->height * new_image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header->size = size * sizeof(struct pixel) + 54;
	
	int wd = new_image->header->width;
	int rs = 0;
	for (int i = 0; i < new_image->header->height; ++i)
	{
		for (int j = 0; j < wd; ++j)
		{
			rs = (int)(i / factor) * image->header->width  + (int)(j / factor);
			new_image->data[i * wd + j] = image->data[rs];

		}
	}

	return new_image;
}