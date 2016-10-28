#ifndef bmplib_h
#define bmplib_h


typedef struct  MATRIX
{
	unsigned int satir;
	unsigned int sutun;
	unsigned int boyut;
	double *mat;

};

typedef struct BMPH
{
	unsigned char bmpftype;			// bmp türü BM olmalý
	unsigned int  bmpfsize;			// bmp boyutu
	unsigned char reserved1;		// ayrýlmýþ özel alan 1
	unsigned char reserved2;		// ayrýlmýþ özel alan 2
	unsigned int  bmpfoffset;		// rgba baþlangýç adresi
};

typedef struct BMPIH
{
	unsigned int bmpsize;			// bitmap boyutu
	int bmpwidth;					// bitmap en
	int bmpheight;					// bitmap boy
	unsigned short colorplanes;		// renk düzlemi deðeri 1
	unsigned short bperpixel;		// pixel baþýna bit sayýsý
	unsigned int cmptype;			// sýkýþtýrma türü
	unsigned int rawsize;			// renk dolgu boyutu
	int xpixel;						// x deki pixel sayýsý
	int ypixel;						// y deki pixel sayýsý
	unsigned int ncolors;			// renk sayýsý
	unsigned int icolors;			// renk bilgisi 0=tüm renkler önemli
};

typedef struct RGBA
{
	
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
};

typedef struct HSV
{
	unsigned int hue;
	unsigned int saturation;
	unsigned int value;
};

typedef struct BMP
{
	BMPH bmphead;
	BMPIH bmpinfo;
	RGBA **pixels;
};


BMP read_image(char *dosya_adi);

bool write_image(BMP kaynak, char *dosya_adi);

//int Otsu_th(BMP gscaleimg, int *&histo);

void kalibrexyz(double *&kh1, int kh1size, double  *&Sonuc, int paramsize = 11);

void Ch_to_World(double x1, double y1, double x2, double y2, double *&parametre1, double *&parametre2, double *X, double *Y, double *Z);




MATRIX transpoze(MATRIX matrix);


#endif