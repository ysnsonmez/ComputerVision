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
	unsigned char bmpftype;			// bmp t�r� BM olmal�
	unsigned int  bmpfsize;			// bmp boyutu
	unsigned char reserved1;		// ayr�lm�� �zel alan 1
	unsigned char reserved2;		// ayr�lm�� �zel alan 2
	unsigned int  bmpfoffset;		// rgba ba�lang�� adresi
};

typedef struct BMPIH
{
	unsigned int bmpsize;			// bitmap boyutu
	int bmpwidth;					// bitmap en
	int bmpheight;					// bitmap boy
	unsigned short colorplanes;		// renk d�zlemi de�eri 1
	unsigned short bperpixel;		// pixel ba��na bit say�s�
	unsigned int cmptype;			// s�k��t�rma t�r�
	unsigned int rawsize;			// renk dolgu boyutu
	int xpixel;						// x deki pixel say�s�
	int ypixel;						// y deki pixel say�s�
	unsigned int ncolors;			// renk say�s�
	unsigned int icolors;			// renk bilgisi 0=t�m renkler �nemli
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