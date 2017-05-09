//
//  bmp.h
//  earth
//
//  Created by xingguo zhao on 5/1/17.
//  Copyright © 2017 xingguo zhao. All rights reserved.
//

#ifndef bmp_h
#define bmp_h


#endif /* bmp_h */
class AUX_RGBImageRec {
	void convertBGRtoRGB();
public:
	byte *data;
	DWORD sizeX;
	DWORD sizeY;
	bool NoErrors;
	AUX_RGBImageRec(): NoErrors(false), data(NULL) {};
	AUX_RGBImageRec(const char *FileName);
	~AUX_RGBImageRec();
	bool loadFile(const char *FileName);
	friend AUX_RGBImageRec *auxDIBImageLoad(const char *FileName);
};
