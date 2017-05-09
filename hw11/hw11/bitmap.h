/*************************************************************************
  FILE:   bitmap.h
          Manages a bitmap file and loads it into a buffer.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef BITMAP_LOAD_H
#define BITMAP_LOAD_H

#define WORD    unsigned short
#define DWORD   unsigned int
#define LONG    int

typedef struct { 
    WORD    Type; 
    DWORD   Size; 
    DWORD   Reserved;
    DWORD   OffBits; 
} BITMAPFILEHEADERDV; 

typedef struct {
    DWORD  Size; 
    LONG   Width; 
    LONG   Height; 
    WORD   Planes; 
    WORD   BitCount; 
    DWORD  Compression; 
    DWORD  SizeImage; 
    LONG   XPelsPerMeter; 
    LONG   YPelsPerMeter; 
    DWORD  ClrUsed; 
    DWORD  ClrImportant; 
} BITMAPINFOHEADERDV; 

int loadBitmap(const char * filename, char * &buffer, 
               int &width, int &height);
#endif
