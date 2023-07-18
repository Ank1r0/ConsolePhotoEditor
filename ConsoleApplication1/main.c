#define _CRT_SECURE_NO_WARNINGS
#include "bmp.h"
#include <stdlib.h>
#include "transformations.h"
#include "filters.h"


void printBMP(const struct bmp_header* a)
{
	if (a->type == 0x4d42)
	{
		printf("\nType %0x\nsize %d\nreserved1 %d\nreserved2 %d\noffset %d\ndib_size %d\nwidth %d\nheight %d\nplanes %d\n", a->type, a->size, a->reserved1, a->reserved2, a->offset, a->dib_size, a->width, a->height, a->planes);
		printf("bpp %d\ncompression %d\nimage_size %d\nx_ppm %d\ny_ppm %d\nnum_colors %d\nimportant_colors %d\n\n", a->bpp, a->compression, a->image_size, a->x_ppm, a->y_ppm, a->num_colors, a->important_colors);
	}
	else
	{
		printf("It`s not BMP file\n");
	}

}

int main(int argc, char** argv)
{
	printf("Reading...\n");
	char c[51] = {0};
	while(1)
	{
		int count = 0;
		if ((count=fread(c, 1, 50, stdin)) < 50)
			break;

		printf("Read: %d \n%s\n",count, c);
	}
	printf("Finish\n");
	FILE *file = fopen("assets/lenna.bmp", "rb");
	struct bmp_image* image = read_bmp(file);
	fclose(file);
	//
	// struct bmp_image* new_image = scale(image, 0.64);
	// printBMP(new_image->header);
	//
	//
	// file = fopen("new_yard.bmp", "wb");
	// write_bmp(file, new_image);
	// fclose(file);
	//
	// free_bmp_image(image);
	// free_bmp_image(new_image);
	getc(stdin);

	return 0;
}