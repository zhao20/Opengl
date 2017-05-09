/*************************************************************************
  FILE:   bitmap.cc
          Manages a bitmap file and loads it into a buffer.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#include "bitmap.h"
#include <fstream>
#include <iostream>
using namespace std;

// reads the data from a bitmap image and stores it in the
// buffer. also set the dimension parameters.
int loadBitmap(const char * filename, char * &buffer, 
               int &width, int &height)
{       
    ifstream fin;   // Open the file

    fin.open(filename, ios::binary);
    if (!fin.good()) {
        cout << "Could not open the file" << endl;
        return 0;
    }

    BITMAPFILEHEADERDV  bfh;            // Read the bitmap headers
    BITMAPINFOHEADERDV  bih;
    fin.read((char*)&bfh, sizeof(BITMAPFILEHEADERDV)-2);
    fin.read((char*)&bih, sizeof(BITMAPINFOHEADERDV));

    width = bih.Width;
    height = bih.Height;

    // Make sure we can use this bitmap
    if ((bfh.Type != 0x4D42) || // hexidecimal for 'BM' or BitMap
        (bih.Planes != 1) ||
        (bih.BitCount != 24) ||
        (bih.Compression != 0)) {
        cout << "Could not read bitmap" << endl;
        fin.close();
        return false;
    }

    // Read the image data into a buffer
    buffer = new char[bih.Width*bih.Height*3];

    fin.read(buffer, bih.Width*bih.Height*3);
    fin.close();

    // Swap red and blue values in the buffer
    unsigned char temp;
    for(int i = 0; i < bih.Width*bih.Height*3; i += 3) {
        temp = buffer[i];
        buffer[i] = buffer[i+2];
        buffer[i+2] = temp;
    }

    return 1;
}
