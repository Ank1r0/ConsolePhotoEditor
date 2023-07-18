#define _CRT_SECURE_NO_WARNINGS
#include "bmp.h"
#include <stdlib.h>
#include "transformations.h"
#include "filters.h"
#include <string.h>

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

void help()
{
	printf("bmp_editor OPTION [FILE_IN] [FILE_OUT]\n");
	printf("\n-r \t\trotate image right\n-l \t\trotate image left\n-v \t\tflip image vertically\n-h \t\tflip image horizontally\n-e string \textract colors\n-sp \t\tsepia filter\n-b \t\tblur your photo\n-c y,x,h,w \tcrop image from position [y,x] of giwen height and widht\n-g \t\tgreyscale makes your photo white and black\n-s \t\tscale image by factor\n-o file\t\twrite output to file\n-i file\t\tread input from the file\n");
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		help();
		return 0;
	}
	int in_index = -1, out_index = -1;
	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			if (i + 1 < argc)
				in_index = i + 1;
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			if (i + 1 == argc)
			{
				help();
				return 0;
			}
			out_index = i + 1;
		}
	}
	struct bmp_image* image = NULL;
	if (in_index == -1)
	{
		image = read_bmp(stdin);
	}
	else
	{
		FILE* filein = fopen(argv[in_index], "rb");
		image = read_bmp(filein);
		if (!filein)
			return 1;
		fclose(filein);
	}
	struct bmp_image* new_image = NULL;
	for (int j = 0; j < argc; ++j)
	{
		if (strcmp(argv[j], "-r") == 0)
		{
			new_image = rotate_right(image);
			free_bmp_image(image);
			image = new_image;
		}
		else if (strcmp(argv[j], "-l") == 0)
		{
			new_image = rotate_left(image);
			free_bmp_image(image);
			image = new_image;
		}
		else if (strcmp(argv[j], "-c") == 0)
		{
			if (j + 1 < argc) //2
			{
				++j;
				unsigned numb[4], i = 1;
				numb[0] = atoi(argv[j]);
				int d = 1;
				while (argv[j][d] != '\0')
				{
					if (argv[j][d] == ',')
					{
						numb[i++] = atoi(argv[j] + d + 1);
					}
					++d;
				}
				new_image = crop(image, numb[0], numb[1], numb[2], numb[3]);
				free_bmp_image(image);
				image = new_image;
			}
		}
		else if (strcmp(argv[j], "-g") == 0)
		{
			new_image = greyscale(image);
			free_bmp_image(image);
			image = new_image;
		}
		else if (strcmp(argv[j], "-help") == 0)
		{
			help();
			return 0;
		}
	}

	bool res = false;
	if (out_index == -1)
	{
		res = write_bmp(stdout, new_image);
	}
	else
	{
		FILE* fileout = fopen(argv[out_index], "wb");
		res = write_bmp(fileout, new_image);
		if (!fileout)
			return 1;
		fclose(fileout);
	}
	free_bmp_image(new_image);
	return 0;
}