#include <iostream>
#include <fstream>
#include "func.h"
#pragma warning(disable:4996)
using namespace std;


int main()
{
	

	int width = 1920;
	int height = 1080;

	unsigned char*** load;
	unsigned char** downsampled[3] = { 0 };
	unsigned char** antialised[3] = { 0 };
	unsigned char** downsampled_antialised[3] = { 0 };
	unsigned char** reconstructed_ori[3] = { 0 };
	unsigned char** reconstructed_ant[3] = { 0 };


	for(int i = 0; i < 5; i++)
	{
		load = load_file(FILENAME[i], width, height);
		cout << "File : " << FILENAME[i] << " open" << endl;
		for (int j = 0; j < 3; j++)
		{
			
			if (j >= 1)
			{
				downsampled[j] = downsampling(load[j], width / 2, height / 2);

				save_output(downsampled[j], DOWNSAMPLED_FILENAME[i], width / 4, height / 4);

				antialised[j] = gaussian_filtering(load[j], 5, width / 2, height / 2);

				downsampled_antialised[j] = downsampling(antialised[j], width / 2, height / 2);

				save_output(downsampled_antialised[j], AA_DOWNSAMPLED_FILENAME[i], width / 4, height / 4);

				reconstructed_ant[j] = reconstruction(downsampled_antialised[j], width / 4, height / 4);

				reconstructed_ori[j] = reconstruction(downsampled[j], width / 4, height / 4);

				save_output(reconstructed_ant[j], AA_REC_FILENAME[i], width / 2, height / 2);
				save_output(reconstructed_ori[j], REC_FILENAME[i], width / 2, height / 2);
				continue;
			}

			downsampled[j] = downsampling(load[j], width, height);

			save_output(downsampled[j], DOWNSAMPLED_FILENAME[i], width / 2, height / 2);

			antialised[j] = gaussian_filtering(load[j], 5, width, height);

			downsampled_antialised[j] = downsampling(antialised[j], width, height);

			save_output(downsampled_antialised[j], AA_DOWNSAMPLED_FILENAME[i], width / 2, height / 2);

			reconstructed_ant[j] = reconstruction(downsampled_antialised[j], width / 2, height / 2);
			reconstructed_ori[j] = reconstruction(downsampled[j], width / 2, height / 2);

			save_output(reconstructed_ant[j], AA_REC_FILENAME[i], width, height);
			save_output(reconstructed_ori[j], REC_FILENAME[i], width, height);


		}

		cout << "MSE between non-Antialiased image - original image " << calc_MSE(load, reconstructed_ori, width, height) << endl;
		cout << "MSE between Antialiased image - original image " << calc_MSE(load, reconstructed_ant, width, height) << endl;

		for (int j = 0; j < 3; j++)
		{
			delete downsampled[j];
			delete antialised[j];
			delete downsampled_antialised[j];
			delete reconstructed_ant[j];
			delete reconstructed_ori[j];
		}
	}




}


