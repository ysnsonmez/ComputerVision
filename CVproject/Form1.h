#pragma once

#pragma comment(lib, "user32.lib") 
#define _WIN32_WINNT 0x0500
#include <windows.h> 
#include <cstdlib> 
#include <ctime>
#include <string>
#include <cmath>
#include<sstream>
#include "Funcs.h"

namespace CVproject {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	double M[11][8];
	int threshold = 0, etiket_one = 0, etiket_two = 0;
	int frames[10][4], **labelimage, **S_hough, **edgeDir;
	int ***h_buffer;


	public ref class Form1 : public System::Windows::Forms::Form
	{

	private: System::Windows::Forms::Button^  btnHLine;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Button^  btnHisto;
	private: System::Windows::Forms::Button^  btnBinary;
	private: System::Windows::Forms::Button^  btnLabel;
	private: System::Windows::Forms::Button^  btnMoment;
	private: System::Windows::Forms::Button^  btnErosion;
	private: System::Windows::Forms::Button^  btnDilation;
	private: System::Windows::Forms::RichTextBox^  rtbDeger;
	private: System::Windows::Forms::Button^  btnCanny;
	private: System::Windows::Forms::TextBox^  txtLow;
	private: System::Windows::Forms::TextBox^  txtHigh;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ToolStripMenuItem^  refreshFormToolStripMenuItem;
	private: System::Windows::Forms::Button^  btnHTCircle;

	public: Bitmap^ bmpFront;
	public: Bitmap^ bmpimage;

		Form1(void)
		{		
			InitializeComponent();
		}

	protected:
		
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  picImage1;
	private: System::Windows::Forms::OpenFileDialog^  dlgOpen;
	private: System::Windows::Forms::PictureBox^  picImage2;
	private: System::Windows::Forms::PictureBox^  picImage4;
	private: System::Windows::Forms::PictureBox^  picImage3;
	private: System::Windows::Forms::Button^  btnGrey;
	private: System::Windows::Forms::Button^  btnSobel;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refreshFormToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->picImage1 = (gcnew System::Windows::Forms::PictureBox());
			this->dlgOpen = (gcnew System::Windows::Forms::OpenFileDialog());
			this->picImage2 = (gcnew System::Windows::Forms::PictureBox());
			this->picImage4 = (gcnew System::Windows::Forms::PictureBox());
			this->picImage3 = (gcnew System::Windows::Forms::PictureBox());
			this->btnGrey = (gcnew System::Windows::Forms::Button());
			this->btnSobel = (gcnew System::Windows::Forms::Button());
			this->btnHLine = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->btnHisto = (gcnew System::Windows::Forms::Button());
			this->btnBinary = (gcnew System::Windows::Forms::Button());
			this->btnLabel = (gcnew System::Windows::Forms::Button());
			this->btnMoment = (gcnew System::Windows::Forms::Button());
			this->btnErosion = (gcnew System::Windows::Forms::Button());
			this->btnDilation = (gcnew System::Windows::Forms::Button());
			this->rtbDeger = (gcnew System::Windows::Forms::RichTextBox());
			this->btnCanny = (gcnew System::Windows::Forms::Button());
			this->txtLow = (gcnew System::Windows::Forms::TextBox());
			this->txtHigh = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnHTCircle = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1073, 29);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->exitToolStripMenuItem, this->refreshFormToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 25);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(174, 26);
			this->openToolStripMenuItem->Text = L"&Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(174, 26);
			this->exitToolStripMenuItem->Text = L"&Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// refreshFormToolStripMenuItem
			// 
			this->refreshFormToolStripMenuItem->Name = L"refreshFormToolStripMenuItem";
			this->refreshFormToolStripMenuItem->Size = System::Drawing::Size(174, 26);
			this->refreshFormToolStripMenuItem->Text = L"&Refresh Form";
			this->refreshFormToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::refreshFormToolStripMenuItem_Click);
			// 
			// picImage1
			// 
			this->picImage1->Location = System::Drawing::Point(16, 32);
			this->picImage1->Name = L"picImage1";
			this->picImage1->Size = System::Drawing::Size(250, 250);
			this->picImage1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picImage1->TabIndex = 2;
			this->picImage1->TabStop = false;
			this->picImage1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::picImage_MouseClick);
			// 
			// dlgOpen
			// 
			this->dlgOpen->FileName = L"openFileDialog1";
			this->dlgOpen->Filter = L"Bitmap|*.bmp|All Files|*.*";
			// 
			// picImage2
			// 
			this->picImage2->Location = System::Drawing::Point(272, 32);
			this->picImage2->Name = L"picImage2";
			this->picImage2->Size = System::Drawing::Size(250, 250);
			this->picImage2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picImage2->TabIndex = 3;
			this->picImage2->TabStop = false;
			// 
			// picImage4
			// 
			this->picImage4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->picImage4->Location = System::Drawing::Point(272, 288);
			this->picImage4->Name = L"picImage4";
			this->picImage4->Size = System::Drawing::Size(250, 250);
			this->picImage4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picImage4->TabIndex = 4;
			this->picImage4->TabStop = false;
			this->picImage4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::picImage4_MouseClick);
			// 
			// picImage3
			// 
			this->picImage3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->picImage3->Location = System::Drawing::Point(16, 288);
			this->picImage3->Name = L"picImage3";
			this->picImage3->Size = System::Drawing::Size(250, 250);
			this->picImage3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picImage3->TabIndex = 5;
			this->picImage3->TabStop = false;
			// 
			// btnGrey
			// 
			this->btnGrey->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnGrey->Location = System::Drawing::Point(547, 288);
			this->btnGrey->Name = L"btnGrey";
			this->btnGrey->Size = System::Drawing::Size(90, 30);
			this->btnGrey->TabIndex = 6;
			this->btnGrey->Text = L"GrayLevel";
			this->btnGrey->UseVisualStyleBackColor = true;
			this->btnGrey->Click += gcnew System::EventHandler(this, &Form1::btnGrey_Click);
			// 
			// btnSobel
			// 
			this->btnSobel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnSobel->Location = System::Drawing::Point(547, 324);
			this->btnSobel->Name = L"btnSobel";
			this->btnSobel->Size = System::Drawing::Size(90, 30);
			this->btnSobel->TabIndex = 7;
			this->btnSobel->Text = L"Gradient";
			this->btnSobel->UseVisualStyleBackColor = true;
			this->btnSobel->Click += gcnew System::EventHandler(this, &Form1::btnSobel_Click);
			// 
			// btnHLine
			// 
			this->btnHLine->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnHLine->Location = System::Drawing::Point(739, 324);
			this->btnHLine->Name = L"btnHLine";
			this->btnHLine->Size = System::Drawing::Size(90, 30);
			this->btnHLine->TabIndex = 8;
			this->btnHLine->Text = L"Lines";
			this->btnHLine->UseVisualStyleBackColor = true;
			this->btnHLine->Click += gcnew System::EventHandler(this, &Form1::btnHoughLine_Click);
			// 
			// chart1
			// 
			this->chart1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(547, 32);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::None;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::SplineArea;
			series1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			series1->Legend = L"Legend1";
			series1->Name = L"Intensity";
			series1->YValuesPerPoint = 4;
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(514, 250);
			this->chart1->TabIndex = 10;
			this->chart1->Text = L"chart1";
			// 
			// btnHisto
			// 
			this->btnHisto->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnHisto->Location = System::Drawing::Point(643, 288);
			this->btnHisto->Name = L"btnHisto";
			this->btnHisto->Size = System::Drawing::Size(90, 30);
			this->btnHisto->TabIndex = 11;
			this->btnHisto->Text = L"Histogram";
			this->btnHisto->UseVisualStyleBackColor = true;
			this->btnHisto->Click += gcnew System::EventHandler(this, &Form1::btnHisto_Click);
			// 
			// btnBinary
			// 
			this->btnBinary->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnBinary->Location = System::Drawing::Point(739, 288);
			this->btnBinary->Name = L"btnBinary";
			this->btnBinary->Size = System::Drawing::Size(90, 30);
			this->btnBinary->TabIndex = 12;
			this->btnBinary->Text = L"Binary Image";
			this->btnBinary->UseVisualStyleBackColor = true;
			this->btnBinary->Click += gcnew System::EventHandler(this, &Form1::btnBinary_Click);
			// 
			// btnLabel
			// 
			this->btnLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnLabel->Location = System::Drawing::Point(835, 288);
			this->btnLabel->Name = L"btnLabel";
			this->btnLabel->Size = System::Drawing::Size(90, 30);
			this->btnLabel->TabIndex = 13;
			this->btnLabel->Text = L"Labeling";
			this->btnLabel->UseVisualStyleBackColor = true;
			this->btnLabel->Click += gcnew System::EventHandler(this, &Form1::btnLabel_Click);
			// 
			// btnMoment
			// 
			this->btnMoment->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnMoment->Location = System::Drawing::Point(931, 288);
			this->btnMoment->Name = L"btnMoment";
			this->btnMoment->Size = System::Drawing::Size(90, 30);
			this->btnMoment->TabIndex = 14;
			this->btnMoment->Text = L"Moments";
			this->btnMoment->UseVisualStyleBackColor = true;
			this->btnMoment->Click += gcnew System::EventHandler(this, &Form1::btnMoment_Click);
			// 
			// btnErosion
			// 
			this->btnErosion->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnErosion->Location = System::Drawing::Point(930, 324);
			this->btnErosion->Name = L"btnErosion";
			this->btnErosion->Size = System::Drawing::Size(90, 30);
			this->btnErosion->TabIndex = 15;
			this->btnErosion->Text = L"Erosion";
			this->btnErosion->UseVisualStyleBackColor = true;
			this->btnErosion->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnErosion_MouseClick);
			// 
			// btnDilation
			// 
			this->btnDilation->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnDilation->Location = System::Drawing::Point(835, 324);
			this->btnDilation->Name = L"btnDilation";
			this->btnDilation->Size = System::Drawing::Size(90, 30);
			this->btnDilation->TabIndex = 16;
			this->btnDilation->Text = L"Dilation";
			this->btnDilation->UseVisualStyleBackColor = true;
			this->btnDilation->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnDilation_MouseClick);
			// 
			// rtbDeger
			// 
			this->rtbDeger->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->rtbDeger->Location = System::Drawing::Point(566, 426);
			this->rtbDeger->Name = L"rtbDeger";
			this->rtbDeger->Size = System::Drawing::Size(474, 181);
			this->rtbDeger->TabIndex = 17;
			this->rtbDeger->Text = L"";
			// 
			// btnCanny
			// 
			this->btnCanny->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnCanny->Location = System::Drawing::Point(643, 324);
			this->btnCanny->Name = L"btnCanny";
			this->btnCanny->Size = System::Drawing::Size(90, 30);
			this->btnCanny->TabIndex = 18;
			this->btnCanny->Text = L"Canny";
			this->btnCanny->UseVisualStyleBackColor = true;
			this->btnCanny->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnCanny_MouseClick);
			// 
			// txtLow
			// 
			this->txtLow->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->txtLow->Location = System::Drawing::Point(625, 359);
			this->txtLow->Name = L"txtLow";
			this->txtLow->Size = System::Drawing::Size(90, 26);
			this->txtLow->TabIndex = 19;
			this->txtLow->Text = L"190";
			// 
			// txtHigh
			// 
			this->txtHigh->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->txtHigh->Location = System::Drawing::Point(625, 391);
			this->txtHigh->Name = L"txtHigh";
			this->txtHigh->Size = System::Drawing::Size(90, 26);
			this->txtHigh->TabIndex = 20;
			this->txtHigh->Text = L"200";
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(553, 365);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 20);
			this->label1->TabIndex = 21;
			this->label1->Text = L"T low   :";
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(553, 397);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 20);
			this->label2->TabIndex = 22;
			this->label2->Text = L"T high :";
			// 
			// btnHTCircle
			// 
			this->btnHTCircle->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnHTCircle->Location = System::Drawing::Point(739, 360);
			this->btnHTCircle->Name = L"btnHTCircle";
			this->btnHTCircle->Size = System::Drawing::Size(90, 30);
			this->btnHTCircle->TabIndex = 23;
			this->btnHTCircle->Text = L"Circles";
			this->btnHTCircle->UseVisualStyleBackColor = true;
			this->btnHTCircle->Click += gcnew System::EventHandler(this, &Form1::btnHTCircle_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1073, 628);
			this->Controls->Add(this->btnHTCircle);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtHigh);
			this->Controls->Add(this->txtLow);
			this->Controls->Add(this->btnCanny);
			this->Controls->Add(this->rtbDeger);
			this->Controls->Add(this->btnDilation);
			this->Controls->Add(this->btnErosion);
			this->Controls->Add(this->btnMoment);
			this->Controls->Add(this->btnLabel);
			this->Controls->Add(this->btnBinary);
			this->Controls->Add(this->btnHisto);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->btnHLine);
			this->Controls->Add(this->btnSobel);
			this->Controls->Add(this->btnGrey);
			this->Controls->Add(this->picImage3);
			this->Controls->Add(this->picImage4);
			this->Controls->Add(this->picImage2);
			this->Controls->Add(this->picImage1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Form1";
			this->Text = L"Image Processing";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picImage3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
	{
			 
	}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
				 Application::Exit();
	}
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
			 Form1::Refresh();
		if (dlgOpen->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				bmpFront = (Bitmap^)Image::FromFile(dlgOpen->FileName);
				picImage1->Image = bmpFront;
			}
			catch (...)
			{
				MessageBox::Show("This file could not be opened !!");
			}
		}	
		
}
private: System::Void picImage_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
		int CurX = e->X;
		int CurY = e->Y;
		MessageBox::Show(("X Location : " + CurX.ToString()+ " Y Location :  " +CurY.ToString()));
}
private: System::Void btnGrey_Click(System::Object^  sender, System::EventArgs^  e) 
{
		Bitmap^ bmp = (Bitmap^)picImage1->Image;
		Color pColor;
		try{
		for (int i = 0; i < bmp->Width; i++)
			for (int j = 0; j < bmp->Height; j++)
			{
				pColor = bmp->GetPixel(i, j);  
		 			 
				int a = pColor.A;
				int r = pColor.R;
				int g = pColor.G;
				int b = pColor.B;

				int avg = (r + g + b) / 3;

				bmp->SetPixel(i, j, pColor.FromArgb(a,avg,avg,avg));

			}
			picImage2->Image = bmp;
			bmp->Save("grayscale.bmp");
		}
		catch (...)
		{
			//MessageBox::Show("Select a File...");
		}

}
private: System::Void btnSobel_Click(System::Object^  sender, System::EventArgs^  e) 
{
		
		BMP img = read_image("grayscale.bmp");

		Bitmap^ Sobel_bmp = (Bitmap^)picImage1->Image;
		Color sColor;

		int w = img.bmpinfo.bmpwidth;
		int h = img.bmpinfo.bmpheight;
		
		int **pixelsPtr; // **edgeDir;
		edgeDir = new int*[w];
		pixelsPtr = new int*[w];
		for (int i = 0; i < w; i++)
		{
			edgeDir[i] = new int[h];
			pixelsPtr[i] = new int[h];
		}

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				pixelsPtr[i][j] = (int)(img.pixels[i][j].red);
				
			}
		}


		int sob_x[3][3] = { { -1, 0, 1 },
							{ -2, 0, 2 },
							{ -1, 0, 1 } };

		int sob_y[3][3] = { {-1,-2,-1 },
							{ 0, 0, 0 },
							{ 1, 2, 1 } };
		int sumXY, thisAngle, newAngle;
		long  sumX;
		long  sumY;
		ofstream edge("edgedir.txt");
		for (int iy = 0; iy < w; iy++)
		{
			for (int jx = 0; jx < h; jx++)
			{
				

				if (iy == 0 || iy == w - 1 || jx == 0 || jx == h - 1)
					sumXY = 0;
				else
				{
					sumX = 0;
					sumY = 0;
					for (int k = -1; k < 2; k++)
					for (int l = -1; l < 2; l++)
					{
							sumX = sumX + sob_x[k + 1][l + 1] * pixelsPtr[iy + k][jx + l];
							sumY = sumY + sob_y[k + 1][l + 1] * pixelsPtr[iy + k][jx + l];
					}
					sumXY = sqrt(sumX*sumX + sumY*sumY);
				}


				thisAngle = (atan2(sumX, sumY) / PI) * 180.0;		// Calculate actual direction of edge

				/* Convert actual edge direction to approximate value */
				if (((thisAngle < 22.5) && (thisAngle > -22.5)) || (thisAngle > 157.5) || (thisAngle < -157.5))
					newAngle = 0;
				if (((thisAngle > 22.5) && (thisAngle < 67.5)) || ((thisAngle < -112.5) && (thisAngle > -157.5)))
					newAngle = 45;
				if (((thisAngle > 67.5) && (thisAngle < 112.5)) || ((thisAngle < -67.5) && (thisAngle > -112.5)))
					newAngle = 90;
				if (((thisAngle > 112.5) && (thisAngle < 157.5)) || ((thisAngle < -22.5) && (thisAngle > -67.5)))
					newAngle = 135;

				edgeDir[iy][jx] = newAngle;

				edge << edgeDir[iy][jx];
				
				if (sumXY < 0) sumXY = 0;
				if (sumXY > 255) sumXY = 255;
				int a = Sobel_bmp->GetPixel(iy, jx).A;
				Sobel_bmp->SetPixel(iy, jx, sColor.FromArgb(a, sumXY, sumXY, sumXY));

			}
			edge << endl;
		}
		try{
		Sobel_bmp->Save("sobelimage.bmp");
		}
		catch (...){}
		picImage3->Image = Sobel_bmp;
			
		delete pixelsPtr;
}
private: System::Void btnHisto_Click(System::Object^  sender, System::EventArgs^  e) 
{

			 Bitmap^ Otsu_bmp = (Bitmap^)picImage2->Image;
			 Color oColor;

			 BMP Otsu = read_image("grayscale.bmp");
			 int height = Otsu.bmpinfo.bmpheight;
			 int width = Otsu.bmpinfo.bmpwidth; 
			 int w_h = height*width;

			// int threshold;
			 int histo[256];
			 double probility[256];			// yoðunluðun bulunma olasýlýðý
			 double sigma_classes[256];		// sýnýflar arasý varyans
			 double fi[256], W[256];		// ort. deðer
			 double max_sigma;				// max sigma deðeri

			 // Histogram
			 for (int i = 0; i < 256; i++)
				 histo[i] = 0;				// To reset histo array

			 for (int x = 0; x < width; x++)
			 {
				 for (int y = 0; y < height; y++)
				 {
					 histo[Otsu.pixels[x][y].red]++;		// extract the histogram
				 }
			 }

			 // show histogram
			 for (int i = 0; i <= 255; i++)
			 {
				 chart1->Series["Intensity"]->Points->AddXY(i, histo[i]);
			 }
			 
			 // resimdeki parlaklýðýn resimde bulunma olasýlýðý
			 for (int i = 0; i <= 255; i++)
			 {
				 probility[i] = (double)histo[i] / w_h;
			 }


			 // Ort. deðer(fi) ve aðýrlýk katsayýsý(W)
			 W[0] = probility[0];
			 fi[0] = 0.0;      
			 for (int i = 1; i <= 255; i++) 
			 {
				 W[i]  = W[i - 1] + probility[i];
				 fi[i] = fi[i - 1] + i*probility[i];
			 }
			 
			 //sigma ve maxsigma
			 threshold = 0;
			 max_sigma = 0.0;
			 for (int i = 0; i < 255; i++) 
			 {
				 if (W[i] != 0.0 && W[i] != 1.0)
					 sigma_classes[i] = pow(fi[255 - 1] * W[i] - fi[i], 2) / (W[i] * (1.0 - W[i]));
				 else
					 sigma_classes[i] = 0.0;

				 if (sigma_classes[i] > max_sigma) 
				 {
					 max_sigma = sigma_classes[i];
					 threshold = i;
				 }
			 }
			 MessageBox::Show("Eþik Deðeri (Intensity): "+threshold.ToString()+"  "+"Pixel sayýsý: "+histo[threshold].ToString());


}
private: System::Void btnBinary_Click(System::Object^  sender, System::EventArgs^  e) 
{
			 Bitmap^ Otsu_bmp = (Bitmap^)picImage2->Image;
			 Color oColor;

			 BMP Otsu = read_image("grayscale.bmp");
			 int height = Otsu.bmpinfo.bmpheight;
			 int width = Otsu.bmpinfo.bmpwidth;
			 int w_h = height*width;

			 int pixel;
			 for (int i = 0; i < width; i++)
			 {
				 for (int j = 0; j < height; j++)
				 {
					 if (Otsu.pixels[i][j].red < threshold)
						 Otsu.pixels[i][j].red = 0;
					 else
						 Otsu.pixels[i][j].red = 255;

					 pixel = Otsu.pixels[i][j].red;
					 Otsu_bmp->SetPixel(i, j, oColor.FromArgb(pixel, pixel, pixel));
				 }
			 }

			 picImage3->Image = Otsu_bmp;
			 Otsu_bmp->Save("binaryimage.bmp");
}
private: System::Void btnLabel_Click(System::Object^  sender, System::EventArgs^  e) 
{
				
			 Bitmap^ limage =(Bitmap^) picImage1->Image;
			 BMP Binaryimage = read_image("binaryimage.bmp");

				int width = Binaryimage.bmpinfo.bmpwidth;
				int height = Binaryimage.bmpinfo.bmpheight;

				// label matrix
				int **binary;
				labelimage = new int*[width + 1];
				binary = new int*[width + 1];
				for (int i = 0; i < width + 1; i++)
				{
					labelimage[i] = new int[height + 1];
					binary[i] = new int[height + 1];
				}


				for (int i = 0; i < width; i++)
				{
					for (int j = 0; j < height; j++)
					{
						labelimage[i][j] = 0;					  // label matrix reset

						if ((int)(Binaryimage.pixels[i][j].red) == 0)  // creating binary image 0-1
							binary[i][j] = 0;
						else
							binary[i][j] = 1;
					}
				}

				/* Labelling */
				int label = 1, temp[8];

				for (int r = 1; r < width; r++)
				{
					for (int c = 1; c < height; c++)
					{
						if (binary[r][c] == 0 )			// arkaplan laballeme yapýlmýyor.
						{
							labelimage[r][c] = 0;
						}
						else
						{
							
							if (labelimage[r][c - 1]     == 0 &&   // backward  komsulara bakýlabilir.
								labelimage[r - 1][c - 1] == 0 &&
								labelimage[r - 1][c]     == 0 &&
								labelimage[r - 1][c + 1] == 0 &&
								labelimage[r][c + 1]     == 0 &&
								labelimage[r + 1][c + 1] == 0 &&
								labelimage[r + 1][c]     == 0 &&
								labelimage[r + 1][c - 1] == 0)
								labelimage[r][c] = label++;
							else
							{
								labelimage[r][c - 1]     > 0 ? temp[0] = labelimage[r][c - 1]     : temp[0] = 22222222222222;
								labelimage[r - 1][c - 1] > 0 ? temp[1] = labelimage[r - 1][c - 1] : temp[1] = 22222222222222;
								labelimage[r - 1][c]     > 0 ? temp[2] = labelimage[r - 1][c]     : temp[2] = 22222222222222;
								labelimage[r - 1][c + 1] > 0 ? temp[3] = labelimage[r - 1][c + 1] : temp[3] = 22222222222222;
								labelimage[r][c + 1]     > 0 ? temp[4] = labelimage[r][c + 1]     : temp[4] = 22222222222222;
								labelimage[r + 1][c + 1] > 0 ? temp[5] = labelimage[r + 1][c + 1] : temp[5] = 22222222222222;
								labelimage[r][c]         > 0 ? temp[6] = labelimage[r][c]         : temp[6] = 22222222222222;
								labelimage[r + 1][c - 1] > 0 ? temp[7] = labelimage[r + 1][c - 1] : temp[7] = 22222222222222;
								sirala(temp);
								labelimage[r][c] = temp[0];
								// collisionda komþularý merkezle ayný yap.
								if (binary[r][c + 1] != 0)
									labelimage[r][c + 1] = temp[0];

								if (binary[r + 1][c + 1] != 0)
									labelimage[r + 1][c + 1] = temp[0];

								if (binary[r + 1][c] != 0)
									labelimage[r + 1][c] = temp[0];

								if (binary[r + 1][c - 1] != 0)
									labelimage[r + 1][c - 1] = temp[0];

								if (binary[r][c - 1] != 0)
									labelimage[r][c - 1] = temp[0];

								if (binary[r - 1][c - 1] != 0)
									labelimage[r - 1][c - 1] = temp[0];

								if (binary[r - 1][c] != 0)
									labelimage[r - 1][c] = temp[0];

								if (binary[r - 1][c + 1] != 0)
									labelimage[r - 1][c + 1] = temp[0];
								
							}
						}
					}
				}
				/************************************************************************/
				/*label çevre düzeltme*/
				for (int i = 1; i< width; i++)
				{
					for (int j = 1; j < height; j++)
					{
						if(labelimage[i][j] > 0 )
						{
							labelimage[i][j - 1]     > 0 ? temp[0] = labelimage[i][j - 1] : temp[0] = 22222222222222;
							labelimage[i - 1][j - 1] > 0 ? temp[1] = labelimage[i - 1][j - 1] : temp[1] = 22222222222222;
							labelimage[i - 1][j]     > 0 ? temp[2] = labelimage[i - 1][j] : temp[2] = 22222222222222;
							labelimage[i - 1][j + 1] > 0 ? temp[3] = labelimage[i - 1][j + 1] : temp[3] = 22222222222222;
							labelimage[i][j + 1]     > 0 ? temp[4] = labelimage[i][j + 1] : temp[4] = 22222222222222;
							labelimage[i + 1][j + 1] > 0 ? temp[5] = labelimage[i + 1][j + 1] : temp[5] = 22222222222222;
							labelimage[i][j]         > 0 ? temp[6] = labelimage[i][j] : temp[6] = 22222222222222;
							labelimage[i + 1][j - 1] > 0 ? temp[7] = labelimage[i + 1][j - 1] : temp[7] = 22222222222222;
							sirala(temp);

							if (binary[i][j - 1] == 1)
								labelimage[i][j - 1] = temp[0];

							if (binary[i - 1][j - 1] == 1)
								labelimage[i - 1][j - 1] = temp[0];

							if (binary[i - 1][j] == 1)
								labelimage[i - 1][j] = temp[0];

							if (binary[i - 1][j + 1] == 1)
								labelimage[i - 1][j + 1] = temp[0];

							if (binary[i][j + 1] == 1)
								labelimage[i][j + 1] = temp[0];

							if (binary[i + 1][j + 1] == 1)
								labelimage[i + 1][j + 1] = temp[0];

							if (binary[i][j ] == 1)
								labelimage[i][j] = temp[0];

							if (binary[i + 1][j - 1] == 1)
								labelimage[i + 1][j - 1] = temp[0];

						}
					}
				}
				/******************************************************************************/


				//-------- Nesne say ve etiket no düzenle ------------//
				//ofstream yaz("label.txt");
				int ara = 0, objCount = 0;
				for (int t = 1; t <= 50; t++)
				{
					for (int i = 1; i < width; i++)
					{ 
						for (int j = 1; j < height; j++)
						{
							if (labelimage[i][j] == t)
							{	
								objCount++;
								ara = labelimage[i][j];
								for (int k = 0; k < width; k++)
								{
									for (int l = 0; l < height; l++)
									{
										if (labelimage[k][l] == ara)
											labelimage[k][l] = objCount;											
									}
								}
								break;
							}
						}
						if (ara == t)
							break;
					}
				}
				/********************************************************/

				/*Debug Labelling and Painting*/
				array<Color>^colors = gcnew array<Color>
				{
					Color::Blue,    
					Color::Red,     
					Color::Green,   
					Color::Yellow,  
					Color::Magenta, 
					Color::Pink,    
					Color::Gray,    
					Color::Orange,  
					Color::Brown,   
					Color::Beige,
					Color::Chocolate,
					Color::Aqua,
					Color::Bisque,
					Color::Cyan
				}; 

				for (int i = 0; i < width; i++)
				{
					for (int j = 0; j < height; j++)
					{
						if (labelimage[i][j] <= 10)
						limage->SetPixel(i, j, colors[(labelimage[i][j])]);
						//yaz << labelimage[i][j];
					}
					//yaz << endl;
				}
				/***************************/
				picImage4->SizeMode = PictureBoxSizeMode::Zoom;
				picImage4->Image = limage;

				//-------------------baunding-------------//
				//MessageBox::Show(objCount.ToString());
				
;
				for (int index = 1; index <= objCount; index++)
				{
					int left = width, right = 0, top = height, low = 0;
					for (int i = 0; i < width; i++)
					{
						for (int j = 0; j < height; j++)
						{
							if ( index == labelimage[i][j])
							{
								if (i < left)
									left = i;
								if (i > right)
									right = i;
								if (j < top)
									top = j;
								if (j > low)
									low = j;
							}
						}
					}
					frames[index][0] = left;
					frames[index][1] = right;
					frames[index][2] = top;
					frames[index][3] = low;
				}
				delete binary;
				//MessageBox::Show(frames[1][0].ToString() + "***" + frames[1][1].ToString() + "***" + frames[1][2].ToString() + "***" + frames[1][3].ToString());
		
}
private: System::Void btnMoment_Click(System::Object^  sender, System::EventArgs^  e) 
{

			 BMP img = read_image("binaryimage.bmp");

			 int w = img.bmpinfo.bmpwidth;
			 int h = img.bmpinfo.bmpheight;
			 int left, right, top, low;

			 double u[4][4];
			 for (int index = 0; index <= 10; index++)
			 {
					 if (index == 0) continue; // arkaplan etiketi

					 left = frames[index][0];
					 right = frames[index][1];
					 top = frames[index][2];
					 low = frames[index][3];

					 int **a_frame;
					 a_frame = new int*[right - left + 1];
					 for (int i = 0; i < right - left + 1; i++)
					 {
						 a_frame[i] = new int[low - top + 1];
					 }

					 //-------- a_frames dolduruluyor.
					 for (int i = 0; i < w; i++)
					 {
						 for (int j = 0; j < h; j++)
						 {
							 if (i >= left && i <= right && j >= top && j <= low && index == labelimage[i][j])
								 a_frame[i - left][j - top] = 1;
							 else if (i >= left && i <= right && j >= top && j <= low && index != labelimage[i][j])
								 a_frame[i - left][j - top] = 0;
						 }
					 }


					 double X_ort, Y_ort;
					 u[1][0] = calc_u(1, 0, right - left + 1, low - top + 1, a_frame);
					 u[0][1] = calc_u(0, 1, right - left + 1, low - top + 1, a_frame);
					 u[0][0] = calc_u(0, 0, right - left + 1, low - top + 1, a_frame);

					 X_ort = u[1][0] / u[0][0];
					 Y_ort = u[0][1] / u[0][0];
				 
					 for (int i = 0; i < 4; i++)
					 for (int j = 0; j < 4; j++)
						 u[i][j] = calc_u(i, j, right - left + 1, low - top + 1, a_frame);
						
					 M[index][1] = (u[2][0] + u[0][2]);

					 M[index][2] = (u[2][0] - u[0][2]) * 
								   (u[2][0] - u[0][2]) + 4 * 
								   (u[1][1] * u[1][1]);

					 M[index][3] = (u[3][0] - 3 * u[1][2]) * 
								   (u[3][0] - 3 * u[1][2]) + 
								   (3 * u[2][1] - u[3][0]) * 
								   (3 * u[2][1] - u[3][0]);

					 M[index][4] = (u[3][0] + u[1][2]) * 
								   (u[3][0] + u[1][2]) + 
								   (u[2][1] + u[0][3]) * 
								   (u[2][1] + u[0][3]);

					 M[index][5] = (u[3][0] - 3 * u[1][2]) * 
								   (u[3][0] + u[1][2]) * 
								   ((u[3][0] + u[1][2]) * (u[3][0] + u[1][2]) - 3 * ((u[2][1] + u[0][3]) * (u[2][1] + u[0][3]))) + 
								   (3 * u[2][1] - u[0][3]) * 
								   (u[2][1] + u[0][3]) * 
								   (3 * ((u[3][0] + u[1][2]) * (u[3][0] + u[1][2])) - (u[2][1] + u[0][3]) * (u[2][1] + u[0][3]));
				 
					 M[index][6] = (u[2][0] - u[0][2]) * 
								   ((u[3][0] + u[1][2]) * (u[3][0] + u[1][2]) - (u[2][1] + u[0][3]) * (u[2][1] + u[0][3])) +
								   4 * u[1][1] * 
								   (u[3][0] + 3 * u[1][2]) * 
								   (u[2][1] + u[0][3]);

					 M[index][7] = (3 * u[2][1] - u[0][3]) *
								   (u[3][0] + u[1][2]) *
								   ((u[3][0] + u[1][2]) * (u[3][0] + u[1][2]) - 3 * (u[2][1] + u[0][3]) *  (u[2][1] + u[0][3])) -
								   (u[3][0] - 3 * u[1][2]) *
								   (u[2][1] + u[0][3]) *
								   (3 * (u[3][0] + u[1][2]) * (u[3][0] + u[1][2]) - (u[2][1] + u[0][3]) * (u[2][1] + u[0][3]));


					 for (int i = 1; i < 8; i++)
					 {
						 rtbDeger->Text += "M[" + index.ToString() + "][" + i.ToString() + "] = " + M[index][i].ToString() + "\n";
					 }

					 rtbDeger->Text +="left-right , top-low: "+ left.ToString() + "-" + right.ToString() + " ," + top.ToString() + "-" + low.ToString() + "\n\n";
					 delete a_frame;
			 }
}
private: System::Void btnErosion_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{			
			 Bitmap^ b_image = (Bitmap^)picImage3->Image;
			 
			 Color lColor; 
			 
			 int width = b_image->Width;		//Binaryimage.bmpinfo.bmpwidth;
			 int height = b_image->Height;		//Binaryimage.bmpinfo.bmpheight;

			 int **binary;
			 binary = new int*[width + 1];
			 for (int i = 0; i < width + 1; i++)
				 binary[i] = new int[height + 1];

			 for (int i = 0; i < width; i++)
			 {
				 for (int j = 0; j < height; j++)
				 {
					 if ((int)(b_image->GetPixel(i,j).R == 0) ) // creating binary image 0-1
						 binary[i][j] = 0;
					 else
						 binary[i][j] = 1;
				 }
			 }

			 for (int i = 1; i < width ; i++)
			 for (int j = 1; j < height ; j++)
			 {
				 if (binary[i][j] == 0)
				 {
					 if (binary[i][j + 1] == 0 && binary[i + 1][j] == 0 && binary[i + 1][j + 1] == 0 && binary[i + 1][j - 1] == 0)
						 binary[i][j] = 0;
					 else
						 binary[i][j] = 1;
				 }
				 b_image->SetPixel(i, j, lColor.FromArgb((binary[i][j] * 255), (binary[i][j] * 255), (binary[i][j] * 255)));
				
			 }

			 
			 picImage3->Image = b_image;
			 b_image->Save("binaryimage.bmp");
			 delete binary;
			 
			 
}
private: System::Void btnDilation_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	
			 Bitmap^ b_image = (Bitmap^)picImage3->Image;

			 Color lColor;
			 int width = b_image->Width;		//Binaryimage.bmpinfo.bmpwidth;
			 int height = b_image->Height;		//Binaryimage.bmpinfo.bmpheight;
			
			 
			 
			 int **binary;
			 binary = new int*[width + 1];
			 for (int i = 0; i < width + 1; i++)
				 binary[i] = new int[height + 1];

			 for (int i = 0; i < width; i++)
			 {
				 for (int j = 0; j < height; j++)
				 {
					 //MessageBox::Show(b_image->GetPixel(i, j).R.ToString() + "  "+b_image->GetPixel(i, j).G.ToString());

					 if ((int)(b_image->GetPixel(i,j).R == 0))  // creating binary image 0-1
						 binary[i][j] = 0;
					 else
						 binary[i][j] = 1;
				 }
			 }

			 for (int i = 1; i < width; i++)
			 for (int j = 1; j < height; j++)
			 {
				 if (binary[i][j] == 1)
				 {
					 if (binary[i][j + 1] == 0 || binary[i + 1][j] == 0 || binary[i + 1][j + 1] == 0 || binary[i + 1][j - 1] == 0)
						 binary[i][j] = 0;
					 else
						 binary[i][j] = 1;
				 }
				 b_image->SetPixel(i, j, lColor.FromArgb((binary[i][j] * 255), (binary[i][j] * 255), (binary[i][j] * 255)));
				 
			 }
			 
			 picImage3->Image = b_image;
			 b_image->Save("binaryimage.bmp");
			 delete binary;

}
private: System::Void btnCanny_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	
		BMP img = read_image("sobelimage.bmp");
		Bitmap^ non_max = gcnew Bitmap("sobelimage.bmp");
		Bitmap^ hysteresis = gcnew Bitmap("sobelimage.bmp");
		Color sColor;

		int w = img.bmpinfo.bmpwidth;
		int h = img.bmpinfo.bmpheight;

		int T_low = 0, T_high = 0;

		if (txtHigh->Text != "" && txtLow->Text != "")
		{
			T_low = Convert::ToInt16(txtLow->Text);
			T_high = Convert::ToInt16(txtHigh->Text);
		}
		int **edge, **pix;
		edge = new int*[w];
		pix = new int*[w];
		for (int i = 0; i < w; i++)
		{
			pix[i] = new int[h];
			edge[i] = new int[h];
		}

		for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			
			pix[i][j] = (int)img.pixels[i][j].red;
			edge[i][j] = 1;
		}

		ifstream oku("edgedir.txt");
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				oku >> edge[i][j];
			}
		}
		// non-maximum suppression
		for (int i = 1; i < w-1 ; i++)
		{
			for (int j = 1; j < h-1; j++)
			{
				if (edgeDir[i][j] == 0) //this mean edges not vertical. the angle of the edge direction.
				{
					if (pix[i][j] <= pix[i - 1][j] || pix[i][j] <= pix[i + 1][j])
					{
						pix[i][j] = 0;
					}
					//else
						//continue;
						//pix[i][j] = 255;
				}else
				if (edgeDir[i][j] == 45)
				{
					if (pix[i][j] <= pix[i - 1][j - 1] || pix[i][j] <= pix[i + 1][j + 1])
					{
						pix[i][j] = 0;
					}
					//else
						//continue;
						//pix[i][j] = 255;

				}else
				if (edgeDir[i][j] == 90)
				{
					if (pix[i][j] <= pix[i][j - 1] || pix[i][j] <= pix[i][j + 1])
					{
						pix[i][j] = 0;
					}
					//else
						//continue;
						//pix[i][j] = 255;
				}else
				if (edgeDir[i][j] == 135)
				{
					if (pix[i][j] <= pix[i - 1][j + 1] || pix[i][j] <= pix[i + 1][j - 1])
					{
						pix[i][j] = 0;
					}
					//else
						//continue;
						//pix[i][j] = 255;
				}
		
				non_max->SetPixel(i, j, sColor.FromArgb(pix[i][j], pix[i][j], pix[i][j]));

				if (pix[i][j] < T_low)
				{
					pix[i][j] = 0;
				}
				else
				if (pix[i][j] > T_high)
				{
					pix[i][j] = 255;
				}
				else
				{
					if (pix[i - 1][j - 1] > T_high ||
						pix[i - 1][j] > T_high || 
						pix[i - 1][j + 1] > T_high || 
						pix[i][j + 1] > T_high || 
						pix[i + 1][j + 1] > T_high || 
						pix[i + 1][j] > T_high || 
						pix[i + 1][j - 1] > T_high || 
						pix[i][j - 1] > T_high)
						pix[i][j] = 255;
					else
					pix[i][j] = 0;
				}
				
				hysteresis->SetPixel(i, j, sColor.FromArgb(pix[i][j], pix[i][j], pix[i][j]));
				
			}
	
		}
		
		picImage1->Image = hysteresis;
		picImage4->Image = non_max;
		non_max->Save("canny.bmp");
		delete edge;
		delete pix;

}
private: System::Void picImage4_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
			 int X = e->X;
			 int Y = e->Y;
			 
			 BMP im = read_image("grayscale.bmp");
			 int w = im.bmpinfo.bmpwidth, h = im.bmpinfo.bmpheight;
			 picImage4->SizeMode = PictureBoxSizeMode::StretchImage;
			 
			 double error = 0.00; 

			 MessageBox::Show(("X Location : " + X.ToString() + " Y Location :  " + Y.ToString()));
			 if (etiket_one == 0)
				 etiket_one = labelimage[X][Y];
			 else if (etiket_two == 0)
			 {
				 etiket_two = labelimage[X][Y];
				 MessageBox::Show(("one Location : " + etiket_one.ToString() + " two Location :  " + etiket_two.ToString()));
			 }



			 if (etiket_one != 0 && etiket_two != 0)
			 {
				 for (int i = 1; i < 8; i++)
				 {
					 error += pow((M[etiket_two][i] - M[etiket_one][i]), 2.00);
				 }
				 error = log1p(sqrt(error));
				 etiket_one = 0;
				 etiket_two = 0;
				 MessageBox::Show("Karesel hata: " + error.ToString());
			 }




}
private: System::Void refreshFormToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Application::Restart();
}
private: System::Void btnHoughLine_Click(System::Object^  sender, System::EventArgs^  e) {

			 Bitmap^ Houghspace = (Bitmap^)picImage1->Image;
			 Bitmap^ Lines = (Bitmap^)picImage1->Image;
			 BMP img = read_image("canny.bmp");
			 Color hColor;

			 int w = img.bmpinfo.bmpwidth;
			 int h = img.bmpinfo.bmpheight;
			 int w_kare = pow(w, 2);
			 int h_kare = pow(h, 2);

			 int r_max = 0, r_norm = 0;
			 r_max = (int)sqrt(w_kare + h_kare);
			 //if (w >= h)
			 // r_max = 2*(w*sqrt(2));
			 //else
			 // r_max = 2*(h*sqrt(2));
			 r_norm = (r_max / 2);

			 int **img_pix;
			 img_pix = new int*[w];
			 for (int i = 0; i < w; i++)
			 {
				 img_pix[i] = new int[h];
			 }

			 for (int i = 0; i < w; i++)
			 for (int j = 0; j < h; j++)
				 img_pix[i][j] = (int)img.pixels[i][j].red;

			 // r-theta uzayý
			 S_hough = new int*[r_max];
			 for (int i = 0; i < r_max; i++)
			 {
				 S_hough[i] = new int[180];
			 }

			 for (int i = 0; i < r_max; i++) // reset hough space
			 for (int j = 0; j < 180; j++)
				 S_hough[i][j] = 0;

			 // x ve y biliniyor. denklem -> d = x.cos(theta) + y.sin(theta)   --> hough uzayý (d,theta) uzayý
			 int d = 0;
			 //int d_new = (int)(r_size / 2);
			 // double intensity = 0.00;
			// ofstream yaz("hspace.txt");
			 for (int x = 0; x < w; x++)
			 {
				 for (int y = 0; y < h; y++)
				 {
					 if (img_pix[x][y]==255)
					 for (int theta = 0; theta < 180; theta++)
					 {
						 d = (x - w / 2)*cos(theta*PI / 180) + (y - h / 2)*sin(theta*PI / 180);
						 /*if (d < 0)
						 d += r_max;*/

						 //S_hough[d + r_norm][theta] += img_pix[x][y];
						 S_hough[d + r_norm][theta]++;
						 d = 0;
					 }
				 }
			 }
			 int wid = r_max, he = 180;
			 double kx, ky;
			 Point p1, p2;
			 float angle = 0.00, d_buf = 0.0;;
			 //Image^ a = picImage4->Image;
			 Bitmap^ hspace = gcnew Bitmap(wid, he);
			 Graphics^ _L = Graphics::FromImage(Lines);   // Draw lines on grayimage.
			 Graphics^ _H = Graphics::FromImage(hspace);	 // linear probability of occurrence. draw circle.

			 for (int d = 0; d < r_max; d++)
			 {
				 for (int theta = 0; theta < 180; theta++)
				 {
					 //S_hough[d][theta] = (int)(S_hough[d][theta] / 150); // hough space normalization

					 if (S_hough[d][theta] >= 80)
					 {
						 rtbDeger->Text += "Lines  :" + "d : " + d.ToString() + "  " + "angle : " + theta.ToString() + "\n";
						 angle = theta*PI / 180;
						 d_buf = (float)(d - r_norm);


						 if (theta >= 45 && theta <= 135)
						 {
							 //y = (r - x cos(t)) / sin(t)  

							 p1.X = 0;

							 p1.Y = (double)((d_buf - ((p1.X - (w / 2)) * cos(angle))) / sin(angle) + (h / 2));

							 p2.X = w;

							 p2.Y = (double)((d_buf - ((p2.X - (w / 2)) * cos(angle))) / sin(angle) + (h / 2));

						 }

						 else

						 {

							 //x = (r - y sin(t)) / cos(t);  

							 p1.Y = 0;

							 p1.X = (double)((d_buf - ((p1.Y - (h / 2)) * sin(angle))) / cos(angle) + (w / 2));

							 p2.Y = h;

							 p2.X = (double)((d_buf - ((p2.Y - (h / 2)) * sin(angle))) / cos(angle) + (w / 2));

						 }
						 _L->DrawLine(Pens::Red, p1, p2);
						 hspace->SetPixel(d, theta, hColor.FromArgb(255, 255, 255));
					 }
					 else
						 hspace->SetPixel(d, theta, hColor.FromArgb(S_hough[d][theta], S_hough[d][theta], S_hough[d][theta]));
					 //yaz << S_hough[d][theta] << " ";
					 //if (hspace->GetPixel(d, theta).R == 255)
					 //{
						// hspace->SetPixel(d, theta, hColor.Red);
					 //}

				 }
				 //yaz << endl;
			 }
			 picImage4->SizeMode = PictureBoxSizeMode::StretchImage;
			 picImage4->Image = hspace;
			 picImage1->Image = Lines;
			 hspace->Save("Lhough.bmp");

			 delete img_pix;

}
private: System::Void btnHTCircle_Click(System::Object^  sender, System::EventArgs^  e) {

			  Bitmap^ Houghspace= gcnew Bitmap("grayscale.bmp");
			  BMP img = read_image("canny.bmp");
			  Color hColor;
			  Graphics^ _circle = Graphics::FromImage(Houghspace);
			  RectangleF rec;

			  int w = img.bmpinfo.bmpwidth;
			  int h = img.bmpinfo.bmpheight;

			 
			  int Rmax, R, x = 0, y = 0, Rind;
			  double intensity = 0, maxintensity;

			  if (h < w) Rind = h / 2;
			  else Rind = w / 2;

			  h_buffer = new int**[w];
			  for (int i = 0; i<w; i++)
			  {
			 	 h_buffer[i] = new int*[h];
			 	 for (int k = 0; k < h; k++)
			 		 h_buffer[i][k] = new int[Rind];
			  }

			  for (int i = 0; i < w; i++)
			  {
				  for (int j = 0; j < h; j++)
				  {
					  for (int r = 0; r < Rind; r++)
					  {
						  h_buffer[i][j][r] = 0;
					  }
				  }
			  }


			  int **pixels;
			  pixels = new int*[w];
			  for (int i = 0; i < w; i++)
			  {
			 	 pixels[i] = new int[h];
			  }

			  for (int i = 0; i < w; i++)
			  {
			 	 for (int j = 0; j < h; j++)
			 	 {
			 		 pixels[i][j] = (int)(img.pixels[i][j].red);
			 	 }
			  }

			  // circle hough transform
			  for (int a = 0; a < w; a++)
			  for (int b = 0; b < h; b++)
			  {
			 		if (a >= b) Rmax = b;
			 		else Rmax = a;

			 		for (R = 1; R <= Rmax; R++)
			 		{
			 			for (int theta = 0; theta <= 360; theta++)
			 			{
			 				x = a + R*cos(theta);
			 				y = b + R*sin(theta);
			 			
							if (x < w && y < h && pixels[x][y]==255)
								h_buffer[a][b][R]++;
			 			}
			 		}
			  }

			 // normalization
			 for (int k = 0; k < w ; k++)
			 for (int l = 0; l < h; l++)
			 {

			 	for (int m = 10; m < Rind; m++)
			 	{
					if (h_buffer[k][l][m] > 150)
					{
						Houghspace->SetPixel(k,l , hColor.Red);
						rec = RectangleF((k - m), (l - m), 2 * m, 2 * m);
						_circle->DrawEllipse(Pens::Yellow, rec);
						
					}
			 	}
			 }
			  picImage2->Image = Houghspace;
			  Houghspace->Save("houghspace.bmp");
			  delete h_buffer;
}
};
}
