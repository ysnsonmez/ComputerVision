#ifndef funcs_h
#define funcs_h

#include<iostream>
#include<fstream>
#include"bmplib.h"
#define PI 3.14

using namespace System::Drawing;
using namespace std;
void kalibrexyz_280000(double *&kh1, int kh1size, double  *&Sonuc)
{


	int k1_2N = (kh1size / 5) * 2;
	int k1_N = kh1size / 5;


	//p1 için C1Matrix dinamik alan tahsis ettik

	double **C1matrix;
	C1matrix = new double*[k1_2N];
	for (int i = 0; i < k1_2N; i++)
	{
		C1matrix[i] = new double[11];
	}


	//k1buffer 
	double **k1_buffer;
	k1_buffer = new double*[k1_N];
	for (int i = 0; i < k1_N; i++)
	{
		k1_buffer[i] = new double[5];
	}


	for (int i = 0; i < k1_N; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			k1_buffer[i][j] = *kh1++;
		}
	}



	//t1_buffer oluþturduk
	double **t1_buffer;
	t1_buffer = new double *[11];
	for (int i = 0; i < 11; i++)
	{
		t1_buffer[i] = new double[k1_2N];
	}


	//	C1matrix doldurduk 

	for (int i = 0; i < k1_N; i++)
	for (int j = 0; j < (k1_2N - 1); j++)
	{
		if (j < 3)
			C1matrix[i][j] = k1_buffer[i][j];
		if (j == 3)
			C1matrix[i][j] = 1;
		if (j <= 7 && j>3)
			C1matrix[i][j] = 0;
		if (j>7)
		{
			C1matrix[i][j++] = (-(k1_buffer[i][0])*k1_buffer[i][3]);
			C1matrix[i][j++] = (-(k1_buffer[i][1])*k1_buffer[i][3]);
			C1matrix[i][j++] = (-(k1_buffer[i][2])*k1_buffer[i][3]);

		}
	}

	for (int i = k1_N; i < k1_2N; i++)
	for (int j = 0; j < (k1_2N - 1); j++)
	{
		if (j < 3)
		{
			C1matrix[i][j++] = 0;
			C1matrix[i][j++] = 0;
			C1matrix[i][j++] = 0;
			C1matrix[i][j++] = 0;
		}
		if (j <= 6)
		{

			C1matrix[i][j++] = k1_buffer[(i % 6)][0];
			C1matrix[i][j++] = k1_buffer[(i % 6)][1];
			C1matrix[i][j++] = k1_buffer[(i % 6)][2];

		}
		if (j == 7)
			C1matrix[i][j++] = 1;
		if (j>7)
		{
			C1matrix[i][j++] = (-(k1_buffer[(i % 6)][0])*k1_buffer[(i % 6)][4]);
			C1matrix[i][j++] = (-(k1_buffer[(i % 6)][1])*k1_buffer[(i % 6)][4]);
			C1matrix[i][j++] = (-(k1_buffer[(i % 6)][2])*k1_buffer[(i % 6)][4]);
		}

	}



	//C1matrix transpozu t1_buffer da

	for (int i = 0; i < 11; i++)
	for (int j = 0; j < k1_2N; j++)
	{
		t1_buffer[i][j] = C1matrix[j][i];
	}


	//t1_buffer*C1matrix    iþlemi....

	double **mult1_buffer;
	mult1_buffer = new double *[11];
	for (int i = 0; i < 11; i++)
	{
		mult1_buffer[i] = new double[11];
	}


	for (int i = 0; i < 11; i++)				// mult_buffer sýfýrladýk.
	for (int j = 0; j < 11; j++)
	{
		mult1_buffer[i][j] = 0;
	}

	for (int i = 0; i < 11; i++)
	for (int j = 0; j < 11; j++)
	for (int k = 0; k < k1_2N; k++)
		mult1_buffer[i][j] += t1_buffer[i][k] * C1matrix[k][j];			//t1_buffer*C1matrix


	//I_matrix oluþturduk

	double I_matrix[11][11];

	for (int i = 0; i < 11; i++)
	for (int j = 0; j < 11; j++)
	{
		if (i == j)
			I_matrix[i][j] = 1.00;
		else
			I_matrix[i][j] = 0.00;
	}

	// mult1_buffer ýn tersini aldýk


	double diyagon, nondiyagon;

	for (int i = 0; i < 11; i++)
	{
		diyagon = mult1_buffer[i][i];
		for (int j = 0; j < 11; j++)
		{
			mult1_buffer[i][j] = mult1_buffer[i][j] / diyagon;
			I_matrix[i][j] = I_matrix[i][j] / diyagon;
		}
		for (int x = 0; x < 11; x++)
		{
			if (x != i)
			{
				nondiyagon = mult1_buffer[x][i];
				for (int j = 0; j < 11; j++)
				{
					mult1_buffer[x][j] = mult1_buffer[x][j] - (mult1_buffer[i][j] * nondiyagon);
					I_matrix[x][j] = I_matrix[x][j] - (I_matrix[i][j] * nondiyagon);
				}
			}
		}
	}

	// I_matrix(mult1_buffer ýn tersi) * t1_buffer yaptýk

	for (int i = 0; i < 11; i++)
	for (int j = 0; j < k1_2N; j++)										//  I_matrix   t1_buffer
	for (int k = 0; k < 11; k++)									//_____^______   __^__
		mult1_buffer[i][j] += I_matrix[i][k] * t1_buffer[k][j];		//(C^t * C)^-1 *  C^t    = mult1_buffer 



	//Rmatrix tanýmladýk ve doldurduk.

	double **Rmatrix;
	Rmatrix = new double *[k1_2N];
	for (int i = 0; i < k1_2N; i++)
	{
		Rmatrix[i] = new double[1];
	}

	for (int i = 0; i < k1_N; i++)
	{
		Rmatrix[i][0] = k1_buffer[i][3];

	}
	int k = 6;
	for (int i = 0; i < k1_N; i++)
	{
		Rmatrix[k][0] = k1_buffer[i][4];
		k++;
	}

	//Rmatrix ile mult1_buffer çarptýk Parametre a aldýk.
	double **Parametre;
	Parametre = new double *[11];
	for (int i = 0; i < 11; i++)
	{
		Parametre[i] = new double[1];
	}

	for (int i = 0; i < 11; i++)
	for (int j = 0; j < 1; j++)
	for (int k = 0; k < k1_2N; k++)
		Parametre[i][j] += mult1_buffer[i][k] * Rmatrix[k][j];



	//Rmatrix sonuc  a aldýk.

	for (int i = 0; i < 11; i++)
	{

		*Sonuc = Rmatrix[i][0];
		*Sonuc++;

	}
	*Sonuc = 1;



}

void Ch_to_World(double x1, double y1, double x2, double y2, double *&parametre1, double *&parametre2, double *X, double *Y, double *Z)
{
	// A Ve B matrisleri oluþturduk .
	double **Amatrix;
	Amatrix = new double *[4];
	for (int i = 0; i < 4; i++)
	{
		Amatrix[i] = new double[3];
	}
	double **Bmatrix;
	Bmatrix = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		Bmatrix[i] = new double[1];
	}

	// A Matrisi doldurduk
	double p1_buffer[12][1];
	double p2_buffer[12][1];


	for (int i = 0; i < 12; i++)
	{
		p1_buffer[i][0] = *parametre1++;
	}

	for (int i = 0; i < 12; i++)
	{
		p2_buffer[i][0] = *parametre2++;
	}



	Amatrix[0][0] = x1*p1_buffer[8][0] - p1_buffer[0][0];
	Amatrix[0][1] = x1*p1_buffer[9][0] - p1_buffer[1][0];
	Amatrix[0][2] = x1*p1_buffer[10][0] - p1_buffer[2][0];

	Amatrix[1][0] = y1*p1_buffer[8][0] - p1_buffer[4][0];
	Amatrix[1][1] = y1*p1_buffer[9][0] - p1_buffer[5][0];
	Amatrix[1][2] = y1*p1_buffer[10][0] - p1_buffer[6][0];

	Amatrix[2][0] = x2*p2_buffer[8][0] - p2_buffer[0][0];
	Amatrix[2][1] = x2*p2_buffer[9][0] - p2_buffer[1][0];
	Amatrix[2][2] = x2*p2_buffer[10][0] - p2_buffer[2][0];

	Amatrix[3][0] = y2*p2_buffer[8][0] - p2_buffer[4][0];
	Amatrix[3][1] = y2*p2_buffer[9][0] - p2_buffer[5][0];
	Amatrix[3][2] = y2*p2_buffer[10][0] - p2_buffer[6][0];

	Bmatrix[0][0] = p1_buffer[0][3] - x1;
	Bmatrix[0][1] = p1_buffer[0][7] - y1;

	Bmatrix[0][2] = p2_buffer[0][3] - x2;
	Bmatrix[0][3] = p2_buffer[0][7] - y2;

	double	t_buffer[3][4];
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 4; j++)
	{
		t_buffer[i][j] = Amatrix[j][i];
	}
	//çarpma a^t*a

	double mult_buffer[3][3];
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	for (int k = 0; k < 4; k++)
		mult_buffer[i][j] += t_buffer[i][k] * Amatrix[k][j];





	//I_matrix oluþturduk

	double I_matrix[3][3];

	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
		if (i == j)
			I_matrix[i][j] = 1.00;
		else
			I_matrix[i][j] = 0.00;
	}


	//ters

	double diyagon, nondiyagon;

	for (int i = 0; i < 3; i++)
	{
		diyagon = mult_buffer[i][i];
		for (int j = 0; j < 3; j++)
		{
			mult_buffer[i][j] = mult_buffer[i][j] / diyagon;
			I_matrix[i][j] = I_matrix[i][j] / diyagon;
		}
		for (int x = 0; x < 3; x++)
		{
			if (x != i)
			{
				nondiyagon = mult_buffer[x][i];
				for (int j = 0; j < 3; j++)
				{
					mult_buffer[x][j] = mult_buffer[x][j] - (mult_buffer[i][j] * nondiyagon);
					I_matrix[x][j] = I_matrix[x][j] - (I_matrix[i][j] * nondiyagon);
				}
			}
		}
	}



	//çarpma
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		mult_buffer[i][j] = 0;

	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 4; j++)
	for (int k = 0; k < 3; k++)
		mult_buffer[i][j] += I_matrix[i][k] * t_buffer[k][j];

	double Xmatrix[3][1];
	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 1; j++)
	for (int k = 0; k < 4; k++)
		Xmatrix[i][j] += mult_buffer[i][k] * Bmatrix[k][j];



	*X = Xmatrix[0][0];
	*Y = Xmatrix[1][0];
	*Z = Xmatrix[2][0];

}

BMP read_image(char *dosya_adi)
{
	BMP resim;
	ifstream bmp(dosya_adi, ios::binary);

	bmp.read((char*)&resim.bmphead.bmpftype, 2);
	bmp.read((char*)&resim.bmphead.bmpfsize, 4);
	bmp.read((char*)&resim.bmphead.reserved1, 2);
	bmp.read((char*)&resim.bmphead.reserved2, 2);
	bmp.read((char*)&resim.bmphead.bmpfoffset, 4);

	bmp.read((char*)&resim.bmpinfo.bmpsize, 4);
	bmp.read((char*)&resim.bmpinfo.bmpwidth, 4);
	bmp.read((char*)&resim.bmpinfo.bmpheight, 4);
	bmp.read((char*)&resim.bmpinfo.colorplanes, 2);
	bmp.read((char*)&resim.bmpinfo.cmptype, 4);
	bmp.read((char*)&resim.bmpinfo.rawsize, 4);
	bmp.read((char*)&resim.bmpinfo.xpixel, 4);
	bmp.read((char*)&resim.bmpinfo.ypixel, 4);
	bmp.read((char*)&resim.bmpinfo.ncolors, 4);
	bmp.read((char*)&resim.bmpinfo.icolors, 4);

	char padding = 4 - (3 * resim.bmpinfo.bmpwidth) % 4;
	if (padding == 4){ padding = 0; }

	bmp.seekg((int)resim.bmphead.bmpfoffset, ios::beg);

	resim.pixels = new RGBA*[resim.bmpinfo.bmpwidth];
	for (int i = 0; i<resim.bmpinfo.bmpwidth; i++) 
	{
		resim.pixels[i] = new RGBA[resim.bmpinfo.bmpheight]; 
	}

	int buffersize = resim.bmpinfo.bmpwidth * 3 + padding;
	char *buffer;
	buffer = new char[buffersize];
	int j = resim.bmpinfo.bmpheight - 1;

	while (j>-1)
	{
		bmp.read((char*)buffer, buffersize);

		for (int i = 0; i < resim.bmpinfo.bmpwidth; i++) 
		{
			memcpy((char*)&(resim.pixels[i][j]), buffer + 3 * i, 3); 
		}
		j--;
	}
	delete[] buffer;
	bmp.close();
	return resim;
}

bool write_image(BMP kaynak, char *dosya_adi) {
	ofstream bmp(dosya_adi, ios::binary);

	int i, j;
	unsigned char padding = 4 - (3 * kaynak.bmpinfo.bmpwidth) % 4;
	if (padding == 4) { padding = 0; }
	unsigned int row = padding + (kaynak.bmpinfo.bperpixel*kaynak.bmpinfo.bmpwidth) / 8;
	

	bmp.write((char*)&kaynak.bmphead.bmpftype, 2);
	bmp.write((char*)&kaynak.bmphead.bmpfsize, 4);
	bmp.write((char*)&kaynak.bmphead.reserved1, 2);
	bmp.write((char*)&kaynak.bmphead.reserved2, 2);
	bmp.write((char*)&kaynak.bmphead.bmpfoffset, 4);
	bmp.write((char*)&kaynak.bmpinfo.bmpsize, 4);
	bmp.write((char*)&kaynak.bmpinfo.bmpwidth, 4);
	bmp.write((char*)&kaynak.bmpinfo.bmpheight, 4);
	bmp.write((char*)&kaynak.bmpinfo.colorplanes, 2);
	bmp.write((char*)&kaynak.bmpinfo.bperpixel, 2);
	bmp.write((char*)&kaynak.bmpinfo.cmptype, 4);
	bmp.write((char*)&kaynak.bmpinfo.rawsize, 4);
	bmp.write((char*)&kaynak.bmpinfo.xpixel, 4);
	bmp.write((char*)&kaynak.bmpinfo.ypixel, 4);
	bmp.write((char*)&kaynak.bmpinfo.ncolors, 4);
	bmp.write((char*)&kaynak.bmpinfo.icolors, 4);

	unsigned short buffersize = kaynak.bmpinfo.bmpwidth * 3 + padding;
	unsigned char *buffer;
	buffer = new unsigned char[buffersize];
	for (i = 0; i<buffersize; i++) { buffer[i] = 0; }

	j = kaynak.bmpinfo.bmpheight - 1;
	while (j>-1) 
	{
		for (i = 0; i < kaynak.bmpinfo.bmpwidth; i++)
			memcpy((char*)buffer + 3 * i, (char*)&(kaynak.pixels[i][j]), 3);
		
		bmp.write((char*)buffer, buffersize);
		j--;
	}
	delete[] buffer;
	return true;

}

BMP  new_bmp(int en, int boy) {
	BMP im;
	int i, j;
	unsigned char padding = 4 - (3 * en) % 4;
	if (padding == 4) { padding = 0; }
	unsigned int row = padding + (24 * en) / 8;

	im.bmphead.bmpftype= 19778;
	im.bmphead.bmpfsize = (int)(54 + row*boy);
	im.bmphead.reserved1 = 0;
	im.bmphead.reserved2 = 0;
	im.bmphead.bmpfoffset = 54;
	im.bmpinfo.bmpsize = 40;
	im.bmpinfo.bmpwidth = en;  //x pixels of bmp
	im.bmpinfo.bmpheight = boy;
	im.bmpinfo.colorplanes = 1;
	im.bmpinfo.bperpixel = 24;
	im.bmpinfo.cmptype = 0;
	im.bmpinfo.rawsize = row*boy;
	im.bmpinfo.xpixel = 0;
	im.bmpinfo.ypixel = 0;
	im.bmpinfo.ncolors = 0;//pow2(24);
	im.bmpinfo.icolors = 0;
	im.pixels = new RGBA*[en];
	for (i = 0; i<en; i++) 
		im.pixels[i] = new RGBA[boy];

	for (i = 0; i<en; i++)
		for (j = 0; j<boy; j++) 
		{
			im.pixels[i][j].red = 0;
			im.pixels[i][j].green = 0;
			im.pixels[i][j].blue = 0;
			im.pixels[i][j].alpha = 0;
		}
	return im;
}

void sirala(int *dizi) {
	
	int aradeger = 0, i = 0;
	
	while (i < 7) 
	{
		if (dizi[i]>dizi[i + 1]) 
		{
			aradeger = dizi[i];
			dizi[i] = dizi[i + 1];
			dizi[i + 1] = aradeger;
			i = 0;
		}
		else 
			i++;
	}

}

int calc_u(int p, int q, int w, int h, int **binary )
{
	int u = 0;

	for (int j = 0; j < h - 1; j++)
	{
		for (int i = 0; i < w - 1; i++)
		{
			u += (i ^ p) * (j ^ q) * binary[i][j];
		}

	}


	return u;
}

double calc_kernel(int i, int j, double ro)
{
	double kernel = 0;
	kernel = (1 / sqrt(2 * PI*pow(ro, 2.00)))*exp(-(i ^ 2 + j ^ 2) / (2 * pow(ro, 2.00)));
	return kernel;
}

void line(Point p1, Point p2, Bitmap^ image,Color& color) 
{
	
	int dx = abs(p2.X - p1.X), sx = p1.X < p2.X ? 1 : -1;
	int dy = abs(p2.Y - p1.Y), sy = p1.Y < p2.Y ? 1 : -1;
	
	int err = (dx>dy ? dx : -dy) / 2, e2;
	
	int x = (p1.X <p2.X ?  p1.X : p2.X);

	for (;;){
		image->SetPixel(p1.X, p2.Y,color.Red);
		if (p1.X == p2.X && p1.Y == p2.Y) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; p1.X += sx; }
		if (e2 < dy) { err += dx; p1.Y += sy; }
	}
}

#endif