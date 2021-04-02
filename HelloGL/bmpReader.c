#include <stdio.h>
#include <stdlib.h>
/* see http://en.wikipedia.org/wiki/BMP_file_format for an explanation of the bitmap file format
	This program handles colour 24-bit .bmp files with a BITMAPINFOHEADER type header
	The image must be square - to be compatible with OpenGL the width and height must be
	a power of 2 (16, 32, 64, 128, 256, 512, 1024)
*/
typedef unsigned __int16 uint16_t; 
typedef __int32 int32_t; 
typedef unsigned __int32 uint32_t; 
typedef __int64 int64_t; 
typedef unsigned __int64 uint64_t; 

// two characters to identify the bitmap file type
typedef struct  {
  unsigned char magic[2];
}bmpfile_ft;
 
// bit map header file
typedef struct  {
  uint32_t filesz;
  uint16_t creator1;
  uint16_t creator2;
  uint32_t bmp_offset;
}bmpfile_header;

// bitmap info
typedef struct {
  uint32_t header_sz;
  int32_t width;
  int32_t height;
  uint16_t nplanes;
  uint16_t bitspp;
  uint32_t compress_type;
  uint32_t bmp_bytesz;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors;
  uint32_t nimpcolors;
} BITMAPINFOHEADER;

typedef struct {
	unsigned char b, g, r;
} bmp_colour;

BITMAPINFOHEADER bitMapInfo;

void loadBitMap(char * fileName, char * outFileName) {
	bmpfile_ft magic;
	bmpfile_header header;
	int row, col;
	bmp_colour * image_buffer;

	FILE * inFile, * outFile;
	inFile = fopen(fileName, "rb");
	outFile = fopen(outFileName, "wb");
	if (inFile == NULL)
	{
		printf("\ncan't open input %s\n", fileName);
		exit (1);
	}
	printf("\nOpened file\n");
	fread(&magic, sizeof(bmpfile_ft), 1, inFile);
	fread(&header, sizeof(bmpfile_header), 1, inFile);
	fread(&bitMapInfo, sizeof(BITMAPINFOHEADER), 1, inFile);
	if (bitMapInfo.width != bitMapInfo.height)
	{
		printf("\nBitmap is not square\n");
			exit (1);
	}

	// create a buffer to hold each line as it is read in
	image_buffer = (bmp_colour *)malloc(sizeof(bmp_colour) * bitMapInfo.width);

	for (row = 0; row < bitMapInfo.height; row++) {
		fread(image_buffer, sizeof(bmp_colour), bitMapInfo.width, inFile);
		// bmp files store colours in the order blue, green, red
		// need to rearrange to the order red, green, blue 
		for (col = 0; col < bitMapInfo.width; col++)
		{
			putc(image_buffer[col].r, outFile);
			putc(image_buffer[+col].g, outFile);
			putc(image_buffer[col].b, outFile);
		}
	}

	// close the .bmp file and free up memory
	fclose(inFile);
	fclose(outFile);
	free(image_buffer);
}

int main(void) {
	printf("\nStarting program\n");
	loadBitMap("Flower.bmp", "Flower.raw");
}

