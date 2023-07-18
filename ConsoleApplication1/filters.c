#include "filters.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	unsigned size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	if (strcmp(colors_to_keep, "red") == 0)
	{
		for (int i = 0; i < size; ++i)
		{
			new_image->data[i].blue = 0;
			new_image->data[i].green = 0;
			new_image->data[i].red = image->data[i].red;
		}
	}
	else if (strcmp(colors_to_keep, "green") == 0)
	{
		for (int i = 0; i < image->header->height * image->header->width; ++i)
		{
			new_image->data[i].red = image->data[i].red;
			new_image->data[i].blue = image->data[i].blue;
			new_image->data[i].green = 0;
		}
	}
	else if (strcmp(colors_to_keep, "blue") == 0)
	{
		for (int i = 0; i < image->header->height * image->header->width; ++i)
		{
			new_image->data[i].red = image->data[i].red;
			new_image->data[i].green = image->data[i].green;
			new_image->data[i].blue = 0;
		}
	}
	else
	{
		printf("Enter correct colors\n");
		return NULL;
	}
	return new_image;
}
struct bmp_image* greyscale(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	unsigned size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	short ac = 0;

	for (int i = 0; i < size; ++i)
	{
		ac = (int)round((image->data[i].red + image->data[i].green + image->data[i].blue) / 3.0);
		new_image->data[i].red = ac;
		new_image->data[i].green = ac;
		new_image->data[i].blue = ac;
	}
	return new_image;
}

struct bmp_image* sepia(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	unsigned size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;

	for (int i = 0, r, g, b; i < size; ++i)
	{
		r = (int)(image->data[i].red * 0.393 + image->data[i].green * 0.769 + image->data[i].blue * 0.189);
		g = (int)(image->data[i].red * 0.349 + image->data[i].green * 0.686 + image->data[i].blue * 0.168);
		b = (int)(image->data[i].red * 0.272 + image->data[i].green * 0.534 + image->data[i].blue * 0.131);
		new_image->data[i].red = r > 255 ? 255 : r;
		new_image->data[i].green = g > 255 ? 255 : g;
		new_image->data[i].blue = b > 255 ? 255 : b;
	}

	return new_image;
}

struct bmp_image* blur(const struct bmp_image* image)
{
	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	unsigned size = image->header->height * image->header->width;
	new_image->data = malloc(size * sizeof(struct pixel));
	new_image->header = malloc(sizeof(struct bmp_header));
	*new_image->header = *image->header;


	for (int i = 1; i < image->header->height - 1; ++i)
	{
		for (int j = 1; j < image->header->width - 1; ++j)
		{
			int red = 0, green = 0, blue = 0;
			blue = image->data[i * j].blue + image->data[(i + 1) * j].blue + image->data[(i - 1) * j].blue + image->data[(i + 1) * (j + 1)].blue +
				image->data[(i - 1) * (j - 1)].blue + image->data[(i + 1) * (j - 1)].blue + image->data[(i - 1) * (j + 1)].blue +
				image->data[i * (j - 1)].blue + image->data[i * (j + 1)].blue;
			new_image->data[i * j].blue = blue / 9;
			blue = 0;

			green = image->data[i * j].green + image->data[(i + 1) * j].green + image->data[(i - 1) * j].green + image->data[(i + 1) * (j + 1)].green +
				image->data[(i - 1) * (j - 1)].green + image->data[(i + 1) * (j - 1)].green + image->data[(i - 1) * (j + 1)].green +
				image->data[i * (j - 1)].green + image->data[i * (j + 1)].green;
			new_image->data[i * j].green = green / 9;
			green = 0;

			red = image->data[i * j].red + image->data[(i + 1) * j].red + image->data[(i - 1) * j].red + image->data[(i + 1) * (j + 1)].red +
				image->data[(i - 1) * (j - 1)].red + image->data[(i + 1) * (j - 1)].red + image->data[(i - 1) * (j + 1)].red +
				image->data[i * (j - 1)].red + image->data[i * (j + 1)].red;
			new_image->data[i * j].red = red / 9;
			red = 0;
		}
	}

	return new_image;

}