#pragma once
#pragma warning(disable:4996)
using namespace std;
#include <direct.h>

const char* DOWNSAMPLED_FILENAME[5] = {
	"./output/Downsampled_ParkScene_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/Downsampled_ParkScene_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/Downsampled_Kimono1_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/Downsampled_Cactus_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/Downsampled_BQTerrace_1920x1080_yuv420_8bit_frame0.yuv" };

const char* AA_DOWNSAMPLED_FILENAME[5] = {
	"./output/AA_Downsampled_ParkScene_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/AA_Downsampled_ParkScene_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/AA_Downsampled_Kimono1_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/AA_Downsampled_Cactus_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/AA_Downsampled_BQTerrace_1920x1080_yuv420_8bit_frame0.yuv" };

const char* FILENAME[5] = {
	"./ParkScene_1920x1080_yuv420_8bit_frame0.yuv",
	"./ParkScene_1920x1080_yuv420_8bit_frame200.yuv",
	"./Kimono1_1920x1080_yuv420_8bit_frame0.yuv",
	"./Cactus_1920x1080_yuv420_8bit_frame200.yuv",
	"./BQTerrace_1920x1080_yuv420_8bit_frame0.yuv" };

const char* AA_REC_FILENAME[5] = {
	"./output/REC_AA_Downsampled_ParkScene_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/REC_AA_Downsampled_ParkScene_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/REC_AA_Downsampled_Kimono1_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/REC_AA_Downsampled_Cactus_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/REC_AA_Downsampled_BQTerrace_1920x1080_yuv420_8bit_frame0.yuv" };

const char* REC_FILENAME[5] = {
	"./output/REC_Downsampled_ParkScene_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/REC_Downsampled_ParkScene_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/REC_Downsampled_Kimono1_1920x1080_yuv420_8bit_frame0.yuv",
	"./output/REC_Downsampled_Cactus_1920x1080_yuv420_8bit_frame200.yuv",
	"./output/REC_Downsampled_BQTerrace_1920x1080_yuv420_8bit_frame0.yuv" };

unsigned char*** load_file(const char* filename, int width, int height)
{
	FILE* file = fopen(filename, "r");

	if(file == NULL)
	{
		cout << "File Open Failed" << endl;
	}
	auto* arr = new unsigned char[(width * height) * 6 / 4];
	fread(arr, 1, ((width * height) * 6 / 4), file);
	auto** arr_y = new unsigned char* [height];
	for(int i = 0; i < height; i++)
	{
		arr_y[i] = new unsigned char[width];
	}

	auto** arr_cb = new unsigned char* [height/2];
	for (int i = 0; i < height/2; i++)
	{
		arr_cb[i] = new unsigned char[width/2];
	}

	auto** arr_cr = new unsigned char* [height/2];
	for (int i = 0; i < height/2; i++)
	{
		arr_cr[i] = new unsigned char[width/2];
	}
	auto*** ptr_arr = new unsigned char** [3];
	ptr_arr[0] = arr_y;
	ptr_arr[1] = arr_cb;
	ptr_arr[2] = arr_cr;

	int count = 0;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			arr_y[i][j] = arr[count];
			count++;
		}
	}

	for (int i = 0; i < height/2; i++)
	{
		for (int j = 0; j < width/2; j++)
		{
			arr_cb[i][j] = arr[count];
			count++;
		}
	}

	for (int i = 0; i < height / 2; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			arr_cr[i][j] = arr[count];
			count++;
		}
	}
	delete arr;

	return ptr_arr;
}


unsigned char** copy_padding(unsigned char** ori, int width, int height)
{
	auto** arr = new unsigned char* [height+2];
	for (int i = 0; i < height+2; i++)
	{
		arr[i] = new unsigned char[width+2];
	}

	arr[0][0] = ori[0][0];
	arr[height + 1][width + 1] = ori[height-1][width-1];
	arr[0][width + 1] = ori[0][width-1];
	arr[height + 1][0] = ori[height-1][0];

	for (int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			arr[i + 1][j + 1] = ori[i][j];
		}
	}
	for (int i = 0; i < width; i++)
	{
		arr[0][i + 1] = ori[0][i];
		arr[height + 1][i + 1] = ori[height-1][i];
	}
	for (int i = 0; i < height; i++)
	{
		arr[i+1][0] = ori[i][0];
		arr[i+1][width+1] = ori[i][width-1];
	}

	return arr;
}


unsigned char** downsampling(unsigned char** ori, int width, int height)
{
	auto** arr = new unsigned char* [height/2];
	for (int i = 0; i < height/2; i++)
	{
		arr[i] = new unsigned char[width/2];
	}

	for (int i = 0; i < height/2; i++)
	{
		for (int j = 0; j < width/2; j++)
		{
			arr[i][j] = ori[(i * 2) + 1][(j * 2) + 1];
		}
	}

	return arr;
}

unsigned char** gaussian_filtering(unsigned char ** ori, const int filtersize, int width, int height)
{
	float gaussian_filter[5][5] = {
	{1, 4, 7, 4, 1},
	{4, 16, 26, 16, 4},
	{7, 26, 41, 26, 7},
	{4, 16, 26, 16, 4},
	{1, 4, 7, 4, 1} };

	auto** filtered = new unsigned char *[height];
	for (int i = 0; i < height; i++)
	{
		filtered[i] = new unsigned char[width];
	}

	unsigned char** padding_1 = copy_padding(ori, width, height);
	unsigned char** padding_2 = copy_padding(padding_1, width+2, height+2);

	//set gaussian filter
	for (int i = 0; i < filtersize; i++)
	{
		for (int j = 0; j < filtersize; j++)
		{
			gaussian_filter[i][j] = gaussian_filter[i][j] / 273;
		}
	}
	float temp =  0;
	//calculate 2d convolution with gaussian filter
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < filtersize; k++) 
			{
				for (int l = 0; l < filtersize; l++)
				{
					temp = temp + (padding_2[i+k][j+l] * gaussian_filter[k][l]);
				}
			}
			filtered[i][j] = (unsigned char)temp;
			temp = 0;
		}
	}
	delete padding_1;
	delete padding_2;
	return filtered;
}

unsigned char  DCT_IF(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
	float res = 0;
	res = (a * 11) - (b * 43) + (c * 160) + (d * 160) - (e * 43) + (f * 11);
	res = res / 256;
	return (unsigned char)res;
}

unsigned char** reconstruction(unsigned char ** ori, const int width, const int height)
{
	auto** rec = new unsigned char* [height * 2];
	for (int i = 0; i < height * 2; i++)
	{
		rec[i] = new unsigned char[width * 2];
	}

	unsigned char ** padding_1 = copy_padding(ori, width, height);
	unsigned char ** padding_2 = copy_padding(padding_1, width+2, height+2);
	unsigned char ** padding_3 = copy_padding(padding_2, width+4, height+4);
	unsigned char** hor_int = new unsigned char* [height];
	for (int i = 0; i < height; i++)
	{
		hor_int[i] = new unsigned char[width];
	}

	for (int i = 0; i < height * 2; i += 2)
	{
		for (int j = 0; j < width * 2; j += 2)
		{
			rec[i + 1][j] = DCT_IF(padding_3[i / 2+1][j / 2], padding_3[i / 2+1][j / 2 + 1], padding_3[i / 2+1][j / 2 + 2],
				padding_3[i / 2+1][j / 2 + 3], padding_3[i / 2+1][j / 2 + 4], padding_3[i / 2+1][j / 2 + 5]);
			rec[i][j+1] = DCT_IF(padding_3[i / 2][j / 2+1], padding_3[i / 2 + 1][j / 2+1], padding_3[i / 2 + 2][j / 2+1],
				padding_3[i / 2 + 3][j / 2+1], padding_3[i / 2 + 4][j / 2+1], padding_3[i / 2 + 5][j / 2+1]);
			hor_int[i / 2][j / 2] = rec[i][j + 1];
		}
	}
	unsigned char** hor_padding_1 = copy_padding(hor_int, width, height);
	unsigned char** hor_padding_2 = copy_padding(hor_padding_1, width + 2, height + 2);
	unsigned char** hor_padding_3 = copy_padding(hor_padding_2, width + 4, height + 4);
	for (int i = 0; i < height * 2; i += 2)
	{
		for (int j = 0; j < width * 2; j += 2)
		{
			rec[i][j] = DCT_IF(hor_padding_3[i / 2][j / 2], hor_padding_3[i / 2][j / 2 + 1], hor_padding_3[i / 2][j / 2 + 2],
				hor_padding_3[i / 2][j / 2 + 3], hor_padding_3[i / 2][j / 2 + 4], hor_padding_3[i / 2][j / 2 + 5]);
			rec[i + 1][j + 1] = padding_3[i / 2 + 1][j / 2 + 1];
		}
	}
	
	delete hor_padding_1;
	delete hor_padding_2;
	delete padding_1;
	delete padding_2;
	delete padding_3;
	return rec;
}

float calc_MSE(unsigned char*** ori, unsigned char*** rec, const int width, const int height)
{
	float mse = 0;

	int total_pixel = width * height / 4 * 6;

	long long int sum = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum = sum + pow((rec[0][i][j] - ori[0][i][j]), 2);
			if ((i < height / 2) && (j < width / 2))
			{
				sum = sum + pow((rec[1][i][j] - ori[1][i][j]), 2);
				sum = sum + pow((rec[2][i][j] - ori[2][i][j]), 2);
			}
		}
	}

	mse = (float)sum / (float)total_pixel;

	return mse;
}

void save_output(unsigned char** ori, const char* filename, const int width, const int height)
{
	FILE* outputfile;
	_mkdir("output");
	if ((outputfile = fopen(filename, "a+t")) == NULL)
	{
		cout << "output File Open Fail" << endl;
		return;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fprintf(outputfile, "%c", ori[i][j]);
		}
	}
	fclose(outputfile);
	return;
}

