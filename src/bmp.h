#ifndef BMP_H_
# define BMP_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
  uint16_t	bfType;
  uint32_t	bfSize;
  uint16_t	bfReserved1;
  uint16_t	bfReserved2;
  uint32_t	bfOffBits;
}		bmpFHEAD;

typedef struct bmpIHEAD
{
  uint32_t	biSize;
  int32_t	biWidth;
  int32_t	biHeight;
  uint16_t	biPlanes;
  uint16_t	biBitCount;
  uint32_t	biCompression;
  uint32_t	biSizeImage;
  int32_t	biXPelsPerMeter;
  int32_t	biYPelsPerMeter;
  uint32_t	biClrUsed;
  uint32_t	biClrImportant;
}		bmpIHEAD;

typedef struct
{
  uint8_t	r;
  uint8_t	g;
  uint8_t	b;
}		pixel;

typedef struct
{
  uint32_t	width;
  uint32_t	height;
  uint8_t	*data;
}		BMP;

int32_t bmp_save(BMP *bmp, char *filename);
int bmp_savebm(BMP *bmp, char *filename);

#endif /* !BMP_H_ */
